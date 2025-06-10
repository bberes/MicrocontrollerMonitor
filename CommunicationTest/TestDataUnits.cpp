#include "pch.h"

// #Kernel
#include "Types\ByteArray.hpp"

// #Communication
#include "Protocols\HiTerm\Commands\Ping.hpp"
#include "Protocols\HiTerm\DataUnits\Frame.hpp"
#include "Protocols\HiTerm\DataUnits\Packet.hpp"
#include "Protocols\HiTerm\Utilities\MessageStore.hpp"
#include "Protocols\HiTerm\Utilities\ProcessorID.hpp"


using namespace Communication::HiTerm;


constexpr UInt8 ByteX12 = 0x12;
constexpr UInt8 ByteX34 = 0x34;


TEST (TestDataUnits, Serialization)
{
	ProcessorID procID (ByteX12, DeviceRole::Master);
	Ping::Command ping (ByteX34);

	Packet packet (ping, procID);
	Frame frame (packet);
	ByteArray byteArray (frame);

	Frame rFrame (byteArray);
	Packet rPacket (rFrame);

	MessageStore ms;
	ms.Register (ping);
	ProcessorID rProcID (ForDeserialization);
	auto message = rPacket.GetMessage (ms, rProcID);

	// #TODO
	EXPECT_TRUE (false);
}