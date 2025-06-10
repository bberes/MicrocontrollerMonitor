#include "MessageTypeID.hpp"

// #Standard
#include <stdexcept>


static UInt8 ToUInt8 (Communication::HiTerm::MessageType mt)
{
	using namespace Communication::HiTerm;
	switch (mt) {
	case MessageType::Command:
	case MessageType::Response:
		break;
	default:
		throw std::invalid_argument ("{21FDB3DC-C2CB-4830-89A8-E5417B9EE1C6}");
	}
	return static_cast<UInt8> (mt);
}


Communication::HiTerm::MessageTypeID::MessageTypeID (MessageType type, UInt8 id)
	: typeID (ToUInt8 (type))
{
	typeID = (typeID << 8) | id;
}


static Communication::HiTerm::MessageType ToMessageType (Communication::HiTerm::DeviceRole dr)
{
	using namespace Communication::HiTerm;
	switch (dr) {
	case DeviceRole::Master:	return MessageType::Command;
	case DeviceRole::Slave:		return MessageType::Response;
		break;
	default:
		throw std::invalid_argument ("{6D18411C-8FBC-4658-8FE0-95C9EB40C216}");
	}
}


Communication::HiTerm::MessageTypeID::MessageTypeID (DeviceRole role, UInt8 id)
	: MessageTypeID (ToMessageType (role), id)
{
}


Communication::HiTerm::MessageTypeID::operator UInt16 () const
{
	return typeID;
}