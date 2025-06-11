#include "Reboot.hpp"

// #Kernel
#include "Utilities\Debug.hpp"
#include "Utilities\Memory.hpp"

// #Communication
#include "Protocols\HiTerm\HiTermCommandIDs.hpp"


UInt8 Communication::HiTerm::Reboot::GetID ()
{
	return HiTerm::CommandID::REBOOT;
}


Communication::HiTerm::Reboot::Command* Communication::HiTerm::Reboot::Command::New (DeserializationSelector ds) const
{
	return MakeRaw<Command> (ds);
}


UInt8 Communication::HiTerm::Reboot::Command::GetID () const
{
	return Reboot::GetID ();
}


UInt16 Communication::HiTerm::Reboot::Command::GetLength () const
{
	return 0u;
}


size_t Communication::HiTerm::Reboot::Command::ReadData (DataStream& /*ds*/, UInt16 length)
{
	if (length != 0u) {
		TODO; // #TODO_ExceptionHandling
	}

	return 0u;
}


size_t Communication::HiTerm::Reboot::Command::WriteData (DataStream& /*ds*/) const
{
	return 0u;
}


Communication::HiTerm::Reboot::Response* Communication::HiTerm::Reboot::Response::New (DeserializationSelector ds) const
{
	return MakeRaw<Response> (ds);
}


UInt8 Communication::HiTerm::Reboot::Response::GetID () const
{
	return Reboot::GetID ();
}


UInt16 Communication::HiTerm::Reboot::Response::GetLength () const
{
	return 0u;
}


size_t Communication::HiTerm::Reboot::Response::ReadData (DataStream& /*ds*/, UInt16 length)
{
	if (length != 0u) {
		TODO; // #TODO_ExceptionHandling
	}

	return 0u;
}


size_t Communication::HiTerm::Reboot::Response::WriteData (DataStream& /*ds*/) const
{
	return 0u;
}