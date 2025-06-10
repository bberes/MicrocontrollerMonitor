#include "DataReceiver.hpp"

// #Kernel
#include "Utilities\LoggerProxy.hpp"

// #Network
#include "Interfaces\DataProcessor.hpp"


Network::DataReceiver::DataReceiver (Utilities::Logger& logger)
	: logger	(logger)
	, processor	(nullptr)
{
}


Network::DataReceiver::~DataReceiver () = default;


void Network::DataReceiver::Set (DataProcessor& dp)
{
	processor = &dp;
}


void Network::DataReceiver::Receive (const ByteArray& byteArray)
{
	buffer.append (byteArray);
	if (processor == nullptr) {
		logger.LogWarning ("{D45CCF0F-5947-4953-9005-91622A0EA278}", "DataReceiver has no processor!");
		return;
	}
	processor->Process (buffer);
}