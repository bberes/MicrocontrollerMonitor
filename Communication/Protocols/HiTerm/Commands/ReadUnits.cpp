#include "ReadUnits.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"

// #Communication
#include "Protocols\HiTerm\HiTermCommandIDs.hpp"


UInt8 Communication::HiTerm::ReadUnits::GetID ()
{
	return HiTerm::CommandID::READ_UNITS;
}


Communication::HiTerm::ReadUnits::Command* Communication::HiTerm::ReadUnits::Command::New (DeserializationSelector ds) const
{
	return new Command (ds);
}


UInt8 Communication::HiTerm::ReadUnits::Command::GetID () const
{
	return ReadUnits::GetID ();
}


UInt16 Communication::HiTerm::ReadUnits::Command::GetLength () const
{
	return 0u;
}


size_t Communication::HiTerm::ReadUnits::Command::ReadData (DataStream& /*ds*/, UInt16 length)
{
	if (length != 0u) {
		TODO; // #TODO_ExceptionHandling
	}

	return 0u;
}


size_t Communication::HiTerm::ReadUnits::Command::WriteData (DataStream& /*ds*/) const
{
	return 0u;
}


Communication::HiTerm::ReadUnits::Response::Response (DeserializationSelector ds)
	: ResponseBase (ds)
{
}


Communication::HiTerm::ReadUnits::Response::Response (UInt8 key, const ByteArray& units)
	: ResponseBase	(key)
	, units			(units)
{
}


Communication::HiTerm::ReadUnits::Response* Communication::HiTerm::ReadUnits::Response::New (DeserializationSelector ds) const
{
	return new Response (ds);
}


UInt8 Communication::HiTerm::ReadUnits::Response::GetID () const
{
	return ReadUnits::GetID ();
}


UInt16 Communication::HiTerm::ReadUnits::Response::GetLength () const
{
	return units.size ();
}


size_t Communication::HiTerm::ReadUnits::Response::ReadData (DataStream& ds, UInt16 length)
{
	units.clear ();
	size_t size = 0u;
	for (UInt16 i = 0u; i < length; ++i) {
		UInt8 unit = 0u;
		size += ::Read (ds, unit);
		units.append (unit);
	}
	return size;
}


size_t Communication::HiTerm::ReadUnits::Response::WriteData (DataStream& ds) const
{
	size_t size = 0u;
	for (auto unit : units) {
		size += ::Write (ds, unit);
	}
	return size;
}