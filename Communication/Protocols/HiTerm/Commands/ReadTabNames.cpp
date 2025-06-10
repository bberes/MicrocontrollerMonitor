#include "ReadTabNames.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"

// #Communication
#include "Protocols\HiTerm\HiTermCommandIDs.hpp"


UInt8 Communication::HiTerm::ReadTabNames::GetID ()
{
	return HiTerm::CommandID::READ_TABNAMES;
}


Communication::HiTerm::ReadTabNames::Command::Command (DeserializationSelector ds)
	: CommandBase (ds)
{
}


Communication::HiTerm::ReadTabNames::Command::Command (UInt8 key)
	: CommandBase (key)
{
}


Communication::HiTerm::ReadTabNames::Command* Communication::HiTerm::ReadTabNames::Command::New (DeserializationSelector ds) const
{
	return new Command (ds);
}


UInt8 Communication::HiTerm::ReadTabNames::Command::GetID () const
{
	return ReadTabNames::GetID ();
}


UInt16 Communication::HiTerm::ReadTabNames::Command::GetLength () const
{
	return 0u;
}


size_t Communication::HiTerm::ReadTabNames::Command::ReadData (DataStream& /*ds*/, UInt16 length)
{
	if (length != 0u) {
		TODO; // #ExceptionHandling
	}

	return 0u;
}


size_t Communication::HiTerm::ReadTabNames::Command::WriteData (DataStream& /*ds*/) const
{
	return 0u;
}


Communication::HiTerm::ReadTabNames::Response::Response (DeserializationSelector ds)
	: ResponseBase (ds)
{
}


Communication::HiTerm::ReadTabNames::Response::Response (UInt8 key, const std::string& name)
	: ResponseBase	(key)
	, name			(name)
{
}


Communication::HiTerm::ReadTabNames::Response* Communication::HiTerm::ReadTabNames::Response::New (DeserializationSelector ds) const
{
	return new Response (ds);
}


UInt8 Communication::HiTerm::ReadTabNames::Response::GetID () const
{
	return ReadTabNames::GetID ();
}


UInt16 Communication::HiTerm::ReadTabNames::Response::GetLength () const
{
	return static_cast<UInt16> (name.size ());
}


size_t Communication::HiTerm::ReadTabNames::Response::ReadData (DataStream& ds, UInt16 length)
{
	name.clear ();
	size_t size = 0u;
	for (UInt16 i = 0u; i < length; ++i) {
		UInt8 byte;
		size += ::Read (ds, byte);
		name += byte;
	}
	return size;
}


size_t Communication::HiTerm::ReadTabNames::Response::WriteData (DataStream& ds) const
{
	size_t size = 0u;
	for (auto c : name) {
		size += ::Write (ds, c);
	}
	return size;
}