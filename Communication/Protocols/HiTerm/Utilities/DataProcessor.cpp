#include "DataProcessor.hpp"

// #Kernel
#include "Utilities\ScopeExit.hpp"

// #Communication
#include "Protocols\HiTerm\DataUnits\Frame.hpp"
#include "DataUnitProcessors.hpp"
#include "FrameIDs.hpp"


Communication::HiTerm::DataProcessor::DataProcessor (FrameProcessor& processor)
	: processor (processor)
{
}


void Communication::HiTerm::DataProcessor::Process (ByteArray& receivedBytes)
{
	qsizetype i = 0u;
	Utilities::ScopeExit processedBytesRemoverOnExit ([&receivedBytes, &i] () {
		receivedBytes.remove (0u, i);
	});

	for ( ; i < receivedBytes.size (); ) {
		const auto& byte = receivedBytes[i++];
		const bool isWaitingForSTX = buffer.isEmpty ();
		buffer.append (byte);
		if (isWaitingForSTX && byte != FrameID::STX) { // ERROR - #TODO This should be logged!
			buffer.clear ();
		}
		if (!isWaitingForSTX && byte == FrameID::STX) { // ERROR - #TODO This should be logged!
			buffer.clear ();
			--i;
		}
		if (!isWaitingForSTX && byte == FrameID::ETX) {
			ByteArray frame;
			buffer.swap (frame);
			FrameReceived (frame);
		}
	}
}


void Communication::HiTerm::DataProcessor::FrameReceived (const ByteArray& byteStream) const
{
	processor.Process (Frame (byteStream));
}