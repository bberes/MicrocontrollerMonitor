#include "Packet.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Types\DataStream.hpp"
#include "Utilities\CRC.hpp"

// #Communication
#include "Protocols\HiTerm\DataUnits\Message.hpp"
#include "Protocols\HiTerm\Exceptions\HiTermExceptions.hpp"
#include "Protocols\HiTerm\Utilities\MessageStore.hpp"
#include "Protocols\HiTerm\Utilities\MessageTypeID.hpp"
#include "Protocols\HiTerm\Utilities\ProcessorID.hpp"


namespace {

using Communication::HiTerm::DeviceRole;
using Communication::HiTerm::MessageType;


void CheckDeviceRole (DeviceRole role, MessageType type)
{
	const bool isMaster = DeviceRole::Master == role;
	const bool isCommand = MessageType::Command == type;
	if (isMaster ^ isCommand) {
		throw std::invalid_argument ("{FE23E7EE-F1FB-4E5D-A916-6FB46C62B997}");
	}
}

}


// This Constructor is used for sending packets only, thus it should
// check consistency between DeviceRole and MessageType.
Communication::HiTerm::Packet::Packet (const Message& message, const ProcessorID& procID)
{
	CheckDeviceRole (procID.GetRole (), message.GetType ());

	DataStream ds (&packet, DataStream::OpenModeFlag::WriteOnly);
	procID.Write (ds);
	Write (ds, message.GetID ());
	message.Write (ds);
	auto crc = Utilities::FastCRC16 (packet);
	Write (ds, crc, ByteOrder::LSBFirst);
}


Communication::HiTerm::Packet::Packet (ByteArray&& packet)
	: packet (packet)
{
}


Communication::HiTerm::MessagePtr Communication::HiTerm::Packet::GetMessage (const MessageStore& ms, ProcessorID& procID) const
{
	DataStream ds (packet);

	size_t size = 0u;
	size += procID.Read (ds);

	UInt8 commandID = 0u;
	size += Read (ds, commandID);

	MessageTypeID typeID (procID.GetRole (), commandID);
	auto message = MessagePtr (ms.CreateNew (typeID));
	size += message->Read (ds);

	UInt16 rCRC = 0u;
	Read (ds, rCRC, ByteOrder::LSBFirst);

	auto subPacket = packet.first (size);
	auto crc = Utilities::FastCRC16 (subPacket);
	if (crc != rCRC) {
		throw MismatchingCRC ("{7102B741-4DF9-4348-AC5D-F2E784CA560B}");
	}

	return message;
}


Communication::HiTerm::Packet::operator const ByteArray& () const
{
	return packet;
}