#include "CommunicationProtocol.hpp"

// #Kernel
#include "Utilities\LoggerProxy.hpp"

// #Network
#include "Connector.hpp"

// #Communication
#include "Requests\Request.hpp"
#include "ResponseListeners.hpp"
#include "Responses.hpp"


Communication::Protocol::Protocol ()
	: logger					(std::make_unique<Utilities::LoggerProxy>	())
	, pingResponse				(std::make_unique<PingResponse>				(*logger))
	, tabDataResponse			(std::make_unique<TabDataResponse>			(*logger))
	, tabValuesResponse			(std::make_unique<TabValuesResponse>		(*logger))
	, readVariablesResponse		(std::make_unique<ReadVariablesResponse>	(*logger))
	, writeVariablesResponse	(std::make_unique<WriteVariablesResponse>	(*logger))
	, readArrayResponse			(std::make_unique<ReadArrayResponse>		(*logger))
	, connector					(nullptr)
{
}


Communication::Protocol::~Protocol () = default;


void Communication::Protocol::SetConnector (Network::Connector& connector)
{
	this->connector = &connector;
}


void Communication::Protocol::SetLogger (Utilities::Logger* logger)
{
	this->logger->SetLogger (logger);
}


void Communication::Protocol::AddListener (PingResponseListener& listener)
{
	pingResponse->Attach (listener);
}


void Communication::Protocol::AddListener (TabDataResponseListener& listener)
{
	tabDataResponse->Attach (listener);
}


void Communication::Protocol::AddListener (TabValuesResponseListener& listener)
{
	tabValuesResponse->Attach (listener);
}


void Communication::Protocol::AddListener (ReadVariablesResponseListener& listener)
{
	readVariablesResponse->Attach (listener);
}


void Communication::Protocol::AddListener (WriteVariablesResponseListener& listener)
{
	writeVariablesResponse->Attach (listener);
}


void Communication::Protocol::AddListener (ReadArrayResponseListener& listener)
{
	readArrayResponse->Attach (listener);
}


bool Communication::Protocol::CheckConnector () const
{
	if (connector == nullptr) {
		logger->LogError ("{23D1D66B-D23A-4DB5-B468-14EA27316E61}", "Request failed due to missing connector.");
		return false;
	}

	if (!connector->IsConnected ()) {
		logger->LogWarning ("{A244E4BA-0DB4-4A9D-B78B-946A7FF15234}", "Request failed due to disconnected status.");
		return false;
	}

	return true;
}


void Communication::Protocol::Transmit (const ByteArray& bytes, const Request& request)
{
	connector->TransmitData (bytes); // #ToDo: handle errors (e.g. connection lost), try-catch?
	logger->LogInfo ("{14477BA0-48A3-43F4-9FDA-0BAD05900E80}", request.ClassName ());
}