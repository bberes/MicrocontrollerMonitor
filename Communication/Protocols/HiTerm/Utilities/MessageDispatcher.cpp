#include "MessageDispatcher.hpp"

// #Communication
#include "Protocols\HiTerm\DataUnits\Message.hpp"
#include "Protocols\HiTerm\Exceptions\HiTermExceptions.hpp"
#include "Protocols\HiTerm\Interfaces\MessageProcessor.hpp"
#include "MessageTypeID.hpp"
#include "ProcessorID.hpp"


Communication::HiTerm::MessageDispatcher::~MessageDispatcher () = default;


static UInt32 GetKey (UInt8 processorID, const Communication::HiTerm::Message& message)
{
	UInt32 key = processorID;
	key <<= 16;
	key |= message.GetTypeID ();
	return key;
}


void Communication::HiTerm::MessageDispatcher::Add (UInt8 processorID, const Message& message, Owner<MessageProcessor> mp)
{
	if (Contains (processorID, message)) {
		throw std::invalid_argument ("{D63D10A6-600C-468A-A93E-A5A79C65AE87}");
	}

	auto key = GetKey (processorID, message);
	processors[key] = std::move (mp);
}


bool Communication::HiTerm::MessageDispatcher::Contains (UInt8 processorID, const Message& message)
{
	auto key = GetKey (processorID, message);
	return processors.count (key) != 0;
}


void Communication::HiTerm::MessageDispatcher::Receive (const Message& message, const ProcessorID& id)
{
	auto key = GetKey (id.GetID (), message);
	if (processors.count (key) != 1) {
		throw MissingTypeID (message.GetTypeID (), "{F51FB7DD-5F8E-401B-9D5B-5744ED336730}");
	}

	processors.at (key)->Process (message);
}