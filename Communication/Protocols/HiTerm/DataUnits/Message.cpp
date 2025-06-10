#include "Message.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"

// #Communication
#include "Protocols\HiTerm\Utilities\MessageTypeID.hpp"


Communication::HiTerm::Message::Message (DeserializationSelector ds)
	: Deserializable (ds)
{
}


Communication::HiTerm::Message::Message (UInt8 key)
	: Deserializable	(RegularConstructor)
	, key				(key)
{
}


Communication::HiTerm::Message::~Message () = default;


Communication::HiTerm::MessageTypeID Communication::HiTerm::Message::GetTypeID () const
{
	return MessageTypeID (GetType (), GetID ());
}


size_t Communication::HiTerm::Message::Read (DataStream& ds)
{
	UInt16 length = 0u;
	size_t size = 0u;
	size += ::Read (ds, key);
	size += ::Read (ds, length, ByteOrder::MSBFirst);
	size += ReadData (ds, length);
	return size;
}


size_t Communication::HiTerm::Message::Write (DataStream& ds) const
{
	size_t size = 0u;
	size += ::Write (ds, key);
	size += ::Write (ds, GetLength (), ByteOrder::MSBFirst);
	size += WriteData (ds);
	return size;
}