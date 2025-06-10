#include "DataUnitProcessors.hpp"

// #Communication
#include "Protocols\HiTerm\DataUnits\Frame.hpp"
#include "Protocols\HiTerm\DataUnits\Message.hpp"
#include "Protocols\HiTerm\DataUnits\Packet.hpp"
#include "Protocols\HiTerm\Interfaces\MessageReceiver.hpp"
#include "ProcessorID.hpp"


Communication::HiTerm::FrameProcessor::FrameProcessor (PacketProcessor& processor)
	: processor (processor)
{
}


void Communication::HiTerm::FrameProcessor::Process (const Frame& frame)
{
	processor.Process (Packet (frame));
}


Communication::HiTerm::PacketProcessor::PacketProcessor (MessageReceiver& mr, const MessageStore& ms)
	: mr (mr)
	, ms (ms)
{
}


void Communication::HiTerm::PacketProcessor::Process (const Packet& packet)
{
	ProcessorID pID (ForDeserialization);
	auto message = packet.GetMessage (ms, pID);
	mr.Receive (*message, pID);
}