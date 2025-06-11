#include "ReadTabValues.hpp"

// #Kernel
#include "Exceptions\KernelExceptions.hpp"
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"
#include "Utilities\Memory.hpp"

// #Communication
#include "Protocols\HiTerm\HiTermCommandIDs.hpp"


UInt8 Communication::HiTerm::ReadTabValues::GetID (MonTabIndex index)
{
	return HiTerm::CommandID::READ_TAB0VALUES + index;
}


Communication::HiTerm::ReadTabValues::Command::Command (DeserializationSelector ds)
	: CommandBase (ds)
{
}


Communication::HiTerm::ReadTabValues::Command::Command (UInt8 key, MonTabIndex index)
	: CommandBase	(key)
	, index			(index)
{
	CheckTabIndex (index);
}


Communication::HiTerm::ReadTabValues::Command* Communication::HiTerm::ReadTabValues::Command::New (DeserializationSelector ds) const
{
	auto m = MakeRaw<Command> (ds);
	m->SetTabIndex (index);
	return m;
}


UInt8 Communication::HiTerm::ReadTabValues::Command::GetID () const
{
	return ReadTabValues::GetID (index);
}


UInt16 Communication::HiTerm::ReadTabValues::Command::GetLength () const
{
	return 0u;
}


size_t Communication::HiTerm::ReadTabValues::Command::ReadData (DataStream& /*ds*/, UInt16 length)
{
	if (length != 0u) {
		TODO; // #ExceptionHandling
	}

	return 0u;
}


size_t Communication::HiTerm::ReadTabValues::Command::WriteData (DataStream& /*ds*/) const
{
	return 0u;
}


Communication::HiTerm::ReadTabValues::Response::Response (DeserializationSelector ds)
	: ResponseBase (ds)
{
}


Communication::HiTerm::ReadTabValues::Response::Response (UInt8 key, MonTabIndex index, const Values& values)
	: ResponseBase	(key)
	, index			(index)
	, values		(values)
{
	CheckTabIndex (index);
}


Communication::HiTerm::ReadTabValues::Response* Communication::HiTerm::ReadTabValues::Response::New (DeserializationSelector ds) const
{
	auto m = MakeRaw<Response> (ds);
	m->SetTabIndex (index);
	return m;
}


UInt8 Communication::HiTerm::ReadTabValues::Response::GetID () const
{
	return ReadTabValues::GetID (index);
}


UInt16 Communication::HiTerm::ReadTabValues::Response::GetLength () const
{
	return static_cast<UInt16> (values.size () * sizeof (UInt32));
}


size_t Communication::HiTerm::ReadTabValues::Response::ReadData (DataStream& ds, UInt16 length)
{
	values.clear ();
	size_t size = 0u;
	for ( ; size < length; ) {
		UInt32 value;
		size += ::Read (ds, value, ByteOrder::MSBFirst);
		if (size > length) {
			throw DataStreamError (DataStreamStatus::ReadPastEnd, "{A11FCEA2-2B2E-4735-9073-1FAF4346FF12}");
		}
		values.push_back (value);
	}
	return size;
}


size_t Communication::HiTerm::ReadTabValues::Response::WriteData (DataStream& ds) const
{
	size_t size = 0u;
	for (auto value : values) {
		size += ::Write (ds, value, ByteOrder::MSBFirst);
	}
	return size;
}