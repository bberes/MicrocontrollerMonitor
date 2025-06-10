#include "Connector.hpp"

// #Qt
#include <QIODevice>

// #Kernel
#include "Exceptions\KernelExceptions.hpp"
#include "Utilities\Logger.hpp"

// #Network
#include "Exceptions\ConnectorExceptions.hpp"
#include "Interfaces\IODeviceProvider.hpp"
#include "Interfaces\Receiver.hpp"


Network::Connector::Connector (Utilities::Logger& logger, Receiver& receiver, Owner<IODeviceProvider> provider)
	: logger	(logger)
	, receiver	(receiver)
	, provider	(std::move (provider))
{
}


Network::Connector::~Connector ()
{
	if (IsConnected ()) {
		Disconnect ();
	}
}


bool Network::Connector::IsConnected () const
{
	return provider->IODevice ().isOpen ();
}


void Network::Connector::Connect ()
{
	auto& ioDevice = provider->IODevice ();
	QObject::connect (&ioDevice, SIGNAL (readyRead ()), this, SLOT (DataReceived ()));

	provider->Connect ();
}


void Network::Connector::Disconnect ()
{
	provider->Disconnect ();

	auto& ioDevice = provider->IODevice ();
	QObject::disconnect (&ioDevice, SIGNAL (readyRead ()), this, SLOT (DataReceived ()));
}


void Network::Connector::TransmitData (const ByteArray& data)
{
	if (data.isEmpty ()) {
		return;
	}

	auto& ioDevice = provider->IODevice ();

	// #ToDo: Connector should be an IODeviceProviderObserver
	if (provider->HasError ()) {
		Disconnect ();
		logger.LogWarning ("{22CFC782-EDB4-465C-9513-C32199D4D3BE}", "Connection is lost.");
		return;
	}

	auto n = ioDevice.write (data);
	if (0 == n) {
		logger.LogWarning ("{0D1AC2B8-68A0-4486-BFE5-6FB766A28670}", "No data was transmitted!");
		throw TransmitError ("{3D28ED10-F453-4AE7-9E88-D0CD055FB97C}");
	}

	// Without this line below no data would be actually sent.
//	ioDevice.waitForBytesWritten (0); // #TODO What number should be here?
}


void Network::Connector::DataReceived ()
{
	auto& ioDevice = provider->IODevice ();
	auto byteArray = ioDevice.readAll ();

	try {
		receiver.Receive (byteArray);
	} catch (const DataStreamError& e) {
		logger.LogWarning ("{A0F3A6DD-6418-4542-8CF3-32B6409473DF}", "DataStreamError occured!", &e);
	} catch (const std::exception& e) {
		logger.LogError ("{D1E00679-AD87-47BC-9F9D-E3C8430FB177}", "Unexpected error occured!", &e);
		throw;
	}
}