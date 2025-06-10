#include "HiTermProtocol.hpp"

// #Kernel
#include "Utilities\Debug.hpp"
#include "Utilities\LoggerProxy.hpp"

// #Communication
#include "Data\TabDataEntry.hpp"
#include "HiTerm\Commands\Ping.hpp"
#include "HiTerm\Commands\ReadBlackboxContent_DEPRECATED.hpp"
#include "HiTerm\Commands\ReadMonTab.hpp"
#include "HiTerm\Commands\ReadVariables_DEPRECATED.hpp"
#include "HiTerm\Commands\ReadTabValues.hpp"
#include "HiTerm\Commands\WriteVariables_DEPRECATED.hpp"
#include "HiTerm\DataUnits\Frame.hpp"
#include "HiTerm\DataUnits\Packet.hpp"
#include "HiTerm\Exceptions\HiTermExceptions.hpp"
#include "HiTerm\Interfaces\MessageProcessor.hpp"
#include "HiTerm\Interfaces\MessageReceiver.hpp"
#include "HiTerm\Utilities\DataProcessor.hpp"
#include "HiTerm\Utilities\DataUnitProcessors.hpp"
#include "HiTerm\Utilities\MessageDispatcher.hpp"
#include "HiTerm\Utilities\MessageStore.hpp"
#include "HiTerm\Utilities\ProcessorID.hpp"
#include "Requests\PingRequest.hpp"
#include "Requests\ReadArrayRequest.hpp"
#include "Requests\ReadVariablesRequest.hpp"
#include "Requests\TabDataRequest.hpp"
#include "Requests\TabValuesRequest.hpp"
#include "Requests\WriteVariablesRequest.hpp"
#include "Responses.hpp"


using namespace Communication::HiTerm;


class Communication::HiTermProtocol::Impl final {
public:
	Impl ();

	void			Register			(const Message& message);
	void			AddProcessor		(UInt8 id, Message& message, MessageProcessorPtr&& mp); // #ToDo: Owner
	DataProcessor&	GetDataProcessor	();

private:
	Owner<MessageDispatcher>	messageDispatcher;
	Owner<MessageStore>			messageStore;
	Owner<PacketProcessor>		packetProcessor;
	Owner<FrameProcessor>		frameProcessor;
	Owner<DataProcessor>		dataProcessor;
};


Communication::HiTermProtocol::HiTermProtocol ()
	: impl (std::make_unique<Impl> ())
{
}


Communication::HiTermProtocol::~HiTermProtocol () = default;


namespace {

ByteArray ConvertToBytes (const Message& message, const UInt8 id)
{
	const ProcessorID processorID (id, DeviceRole::Master);
	const Packet packet (message, processorID);
	const Frame frame (packet);
	return frame;
}

}


namespace {

class PingResponseProcessor final : public MessageProcessor {
public:
	explicit PingResponseProcessor (Communication::PingResponse& response)
		: MessageProcessor	(response)
		, response			(response)
	{
	}

private:
	virtual void ProcessImpl (const Message& message) override
	{
		auto& pingResponse = static_cast<const Ping::Response&> (message);
		auto status = pingResponse.GetStatus ();
		response.SetStatus (ToString (status));
	}

private:
	Communication::PingResponse& response;
};

}


ByteArray Communication::HiTermProtocol::ConvertToBytes (const PingRequest& request)
{
	Ping::Response response (ForDeserialization);
	impl->Register (response);

	auto id = request.GetProcessorID ();
	impl->AddProcessor (id, response, std::make_unique<PingResponseProcessor> (*pingResponse));

	constexpr UInt8 key = 0u;
	const Ping::Command command (key);
	return ::ConvertToBytes (command, id);
}


namespace {

class ReadMonTabResponseProcessor final : public MessageProcessor {
public:
	explicit ReadMonTabResponseProcessor (Communication::TabDataResponse& response)
		: MessageProcessor	(response)
		, response			(response)
	{
	}

private:
	virtual void ProcessImpl (const Message& message) override
	{
		auto& readMonTabResponse = static_cast<const ReadMonTab::Response&> (message);
		auto& monTab = readMonTabResponse.GetMonTab ();
		auto& entries = monTab.GetEntries ();

		Communication::TabDataEntries resultEntries; // #ToDo: extract method
		for (auto& entry : entries) {
			Communication::TabDataEntry e;
			e.name = entry.GetName ();
			e.unit = ToString (entry.GetUnit ());
			e.type = entry.GetType ();
			e.ptr  = entry.GetPtr ();
			e.pMax = entry.GetPMax ();
			e.pMin = entry.GetPMin ();
			resultEntries.push_back (e);
		}

		response.SetEntries (resultEntries);
	}

private:
	Communication::TabDataResponse& response;
};

}


ByteArray Communication::HiTermProtocol::ConvertToBytes (const TabDataRequest& request)
{
	const auto tabIndex = static_cast<MonTabIndex> (request.GetTabIndex ());
	CheckTabIndex (tabIndex);

	ReadMonTab::Response response (ForDeserialization);
	response.SetTabIndex (tabIndex);
	impl->Register (response);

	auto id = request.GetProcessorID ();
	impl->AddProcessor (id, response, std::make_unique<ReadMonTabResponseProcessor> (*tabDataResponse));

	constexpr UInt8 key = 0u;
	const ReadMonTab::Command command (key, tabIndex);
	return ::ConvertToBytes (command, id);
}


namespace {

class ReadTabValuesResponseProcessor final : public MessageProcessor {
public:
	explicit ReadTabValuesResponseProcessor (Communication::TabValuesResponse& response)
		: MessageProcessor	(response)
		, response			(response)
	{
	}

private:
	virtual void ProcessImpl (const Message& message) override
	{
		auto& readTabValuesResponse = static_cast<const ReadTabValues::Response&> (message);
		response.SetValues (readTabValuesResponse.GetValues ());
	}

private:
	Communication::TabValuesResponse& response;
};

}


ByteArray Communication::HiTermProtocol::ConvertToBytes (const TabValuesRequest& request)
{
	const auto tabIndex = static_cast<MonTabIndex> (request.GetTabIndex ());
	CheckTabIndex (tabIndex);

	ReadTabValues::Response response (ForDeserialization);
	response.SetTabIndex (tabIndex);
	impl->Register (response);

	auto id = request.GetProcessorID ();
	impl->AddProcessor (id, response, std::make_unique<ReadTabValuesResponseProcessor> (*tabValuesResponse));

	constexpr UInt8 key = 0u;
	const ReadTabValues::Command command (key, tabIndex);
	return ::ConvertToBytes (command, id);
}


namespace {

Communication::Variables ToVariables (const Variables& hiTermVars)
{
	Communication::Variables variables;
	for (auto& var : hiTermVars) {
		variables.push_back (var);
	}
	return variables;
}


class ReadVariablesResponseProcessor final : public MessageProcessor {
public:
	explicit ReadVariablesResponseProcessor (Communication::ReadVariablesResponse& response)
		: MessageProcessor	(response)
		, response			(response)
	{
	}

private:
	virtual void ProcessImpl (const Message& message) override
	{
		auto& readVariablesResponse = static_cast<const Deprecated::ReadVariables::Response&> (message);
		response.SetVariables (ToVariables (readVariablesResponse.GetVariables ()));
	}

private:
	Communication::ReadVariablesResponse& response;
};


MemoryEntries ToHiTermMemoryEntries (const Communication::MemoryRefs& memoryRefs)
{
	MemoryEntries memoryEntries;
	for (auto& memoryRef : memoryRefs) {
		if (memoryRef.GetAddressSize () != Communication::AddressSize::Size4Bytes) {
			TODO; // #TODO
		}
		auto address = memoryRef.GetAddress<UInt32> ();
		auto size = static_cast<Memory::Size> (memoryRef.GetVariableSize ()); // #ToDo: use converter fn. instead
		memoryEntries.push_back (Memory (address, size));
	}
	return memoryEntries;
}

}


ByteArray Communication::HiTermProtocol::ConvertToBytes (const ReadVariablesRequest& request)
{
	// #ToDo: The SW on the uC supports only the old version. This should be detected automatically.
	Deprecated::ReadVariables::Response response (ForDeserialization);
	impl->Register (response);

	auto id = request.GetProcessorID ();
	impl->AddProcessor (id, response, std::make_unique<ReadVariablesResponseProcessor> (*readVariablesResponse));

	constexpr UInt8 key = 0u;
	const Deprecated::ReadVariables::Command command (key, ToHiTermMemoryEntries (request.GetMemoryRefs ()));
	return ::ConvertToBytes (command, id);
}


namespace {

class WriteVariablesResponseProcessor final : public MessageProcessor {
public:
	explicit WriteVariablesResponseProcessor (Communication::WriteVariablesResponse& response)
		: MessageProcessor	(response)
		, response			(response)
	{
	}

private:
	virtual void ProcessImpl (const Message& message) override
	{
		auto& writeVariablesResponse = static_cast<const Deprecated::WriteVariables::Response&> (message);
		// Maybe check value of writeVariablesResponse.GetKey ()
		response.Notify ();
	}

private:
	Communication::WriteVariablesResponse& response;
};


Variables ToHiTermVariables (const Communication::Variables& variables)
{
	Communication::HiTerm::Variables hiTermVars;
	for (auto& v : variables) {
		hiTermVars.push_back (Variable (v));
	}
	return hiTermVars;
}

}


ByteArray Communication::HiTermProtocol::ConvertToBytes (const WriteVariablesRequest& request)
{
	Deprecated::WriteVariables::Response response (ForDeserialization);
	impl->Register (response);

	auto id = request.GetProcessorID ();
	impl->AddProcessor (id, response, std::make_unique<WriteVariablesResponseProcessor> (*writeVariablesResponse));

	constexpr UInt8 key = 0u; // #ToDo: Should the received key be checked? (Check its role!)
	const Deprecated::WriteVariables::Command command (key, ToHiTermVariables (request.GetVariables ()));
	return ::ConvertToBytes (command, id);
}


namespace {

class ReadBlackboxContentResponseProcessor final : public MessageProcessor {
public:
	explicit ReadBlackboxContentResponseProcessor (Communication::ReadArrayResponse& response)
		: MessageProcessor	(response)
		, response			(response)
	{
	}

private:
	virtual void ProcessImpl (const Message& message) override
	{
		auto& readBlackboxContentResponse = static_cast<const Deprecated::ReadBlackboxContent::Response&> (message);
		auto& bbxContent = readBlackboxContentResponse.GetContent ();
		auto& content    = bbxContent.GetContent ();
		auto& info       = bbxContent.GetInfo ();

		response.SetVariables (content); // #ToDo: temporary solution
	}

private:
	Communication::ReadArrayResponse& response;
};

}


ByteArray Communication::HiTermProtocol::ConvertToBytes (const ReadArrayRequest& request)
{
	Deprecated::ReadBlackboxContent::Response response (ForDeserialization);
	impl->Register (response);

	auto id = request.GetProcessorID ();
	impl->AddProcessor (id, response, std::make_unique<ReadBlackboxContentResponseProcessor> (*readArrayResponse));

	constexpr UInt8 key = 0u;
	const Deprecated::ReadBlackboxContent::Command command (key, BlackboxContent::Info (request.GetAddress (), request.GetLength ()));
	return ::ConvertToBytes (command, id);
}


void Communication::HiTermProtocol::Process (ByteArray& byteArray)
{
	try {
		impl->GetDataProcessor ().Process (byteArray);
	} catch (const MismatchingCRC& e) {
		logger->LogWarning ("{71999572-DFA9-4032-8865-7DBAA98F7F5A}", "Damaged packet received!", &e);
	} catch (const MissingTypeID& e) {
		logger->LogWarning ("{BD5B8078-CADA-48AC-97A6-E143D8C176DF}", "Unregistered message received!", &e);
	} catch (const std::exception& e) {
		logger->LogError ("{587AAE13-6284-4475-92F3-B5B274F415CD}", "Unexpected error occured!", &e);
		throw;
	}
}


Communication::HiTermProtocol::Impl::Impl ()
	: messageDispatcher	(std::make_unique<MessageDispatcher>		())
	, messageStore		(std::make_unique<MessageStore>				())
	, packetProcessor	(std::make_unique<PacketProcessor>			(*messageDispatcher, *messageStore))
	, frameProcessor	(std::make_unique<FrameProcessor>			(*packetProcessor))
	, dataProcessor		(std::make_unique<HiTerm::DataProcessor>	(*frameProcessor))
{
}


void Communication::HiTermProtocol::Impl::Register (const Message& message)
{
	if (messageStore->IsRegistered (message)) {
		return;
	}

	messageStore->Register (message);
}


void Communication::HiTermProtocol::Impl::AddProcessor (UInt8 id, Message& message, MessageProcessorPtr&& mp)
{
	if (messageDispatcher->Contains (id, message)) {
		return;
	}

	messageDispatcher->Add (id, message, std::forward<MessageProcessorPtr> (mp));
}


Network::DataProcessor& Communication::HiTermProtocol::Impl::GetDataProcessor ()
{
	return *dataProcessor;
}