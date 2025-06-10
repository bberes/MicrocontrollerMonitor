#pragma once
#ifndef Communication__HiTerm_DataUnitProcessors__hpp
#define Communication__HiTerm_DataUnitProcessors__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Communication
#include "CommunicationTypes.hpp"


namespace Communication::HiTerm {

class COMMUNICATION_EXPORT FrameProcessor final {
public:
	explicit FrameProcessor (PacketProcessor& processor);

	void Process (const Frame& frame);

private:
	PacketProcessor& processor;
};


class COMMUNICATION_EXPORT PacketProcessor final {
public:
	explicit PacketProcessor (MessageReceiver& mr, const MessageStore& ms);

	void Process (const Packet& packet);

private:
	MessageReceiver&	mr;
	const MessageStore&	ms;
};

}


#endif