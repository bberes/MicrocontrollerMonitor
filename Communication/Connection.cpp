#include "Connection.hpp"

// #Standard
#include <stdexcept>

// #Kernel
#include "Utilities\Logger.hpp"

// #Network
#include "Connector.hpp"
#include "DataReceiver.hpp"
#include "Interfaces\IODeviceProvider.hpp"

// #Communication
#include "CommunicationProtocol.hpp"

// #Note: reconsider dependencies between members: receiver uses protocol, protocol uses connector, connector uses receiver
Communication::Connection::Connection (Utilities::Logger& logger)
	: logger	(logger)
	, protocol	(nullptr)
	, receiver	(std::make_unique<Network::DataReceiver> (logger))
	, connector	(nullptr)
{
}


Communication::Connection::~Connection () = default;


bool Communication::Connection::HasProtocol () const
{
	return protocol != nullptr;
}


void Communication::Connection::SetProtocol (Owner<Protocol> protocol)
{
	this->protocol = std::move (protocol);
	this->protocol->SetLogger (&logger);
	receiver->Set (*this->protocol);
}


Communication::Protocol& Communication::Connection::GetProtocol ()
{
	if (!HasProtocol ()) {
		logger.LogError ("{22BED975-9F30-4764-BA31-FFB5B7BE36AA}", "Missing Protocol!");
		throw std::runtime_error ("{09E3567E-E4DA-4978-898B-38AF9EB21458}");
	}

	return *protocol;
}

// #ToDo: consider passing rvalues (fn. Reset, Connector) if valid, to avoid inclusion of header IODeviceProvider
void Communication::Connection::Reset (Owner<Network::IODeviceProvider> provider)
{
	connector = std::make_unique<Network::Connector> (logger, *receiver, std::move (provider));

	if (!HasProtocol ()) {
		logger.LogError ("{375A3C29-D00C-421D-A2DD-BDD58CDA55F3}", "Missing Protocol!");
		throw std::runtime_error ("{91C7BDD2-266D-4C83-BCA8-2C0A3E75AAF2}");
	}

	protocol->SetConnector (*connector);
}


void Communication::Connection::Connect ()
{
	logger.LogInfo ("{7F5DB180-C512-4B76-9595-790174C08D3A}", "Connecting...");
	connector->Connect ();
	logger.LogInfo ("{CD66C871-880C-45B2-81D0-6FE7E8FC7792}", "Connected");
}


void Communication::Connection::Disconnect ()
{
	logger.LogInfo ("{8B092FC2-FE20-40C4-8029-59C8F02EF920}", "Disconnecting...");
	connector->Disconnect ();
	logger.LogInfo ("{718571DA-0C50-47C6-85DD-71F3395783A5}", "Disconnected");
}