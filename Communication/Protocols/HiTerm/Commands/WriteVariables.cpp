#include "WriteVariables.hpp"

// #Kernel
#include "Utilities\Debug.hpp"

// #Communication
#include "Protocols\HiTerm\Utilities\CommonParts.hpp"
#include "Protocols\HiTerm\HiTermCommandIDs.hpp"


UInt8 Communication::HiTerm::WriteVariables::GetID ()
{
	return HiTerm::CommandID::WRITE_NEW;
}


Communication::HiTerm::WriteVariables::Command::Command (DeserializationSelector ds)
	: CommandBase (ds)
{
}


Communication::HiTerm::WriteVariables::Command::Command (UInt8 key, const Variables& variables)
	: CommandBase	(key)
	, variables		(variables)
{
}


Communication::HiTerm::WriteVariables::Command* Communication::HiTerm::WriteVariables::Command::New (DeserializationSelector ds) const
{
	return new Command (ds);
}


UInt8 Communication::HiTerm::WriteVariables::Command::GetID () const
{
	return WriteVariables::GetID ();
}


UInt16 Communication::HiTerm::WriteVariables::Command::GetLength () const
{
	return static_cast<UInt16> (LengthOf (variables));
}


size_t Communication::HiTerm::WriteVariables::Command::ReadData (DataStream& ds, UInt16 length)
{
	return ::Communication::HiTerm::Read (ds, variables, length);
}


size_t Communication::HiTerm::WriteVariables::Command::WriteData (DataStream& ds) const
{
	return ::Communication::HiTerm::Write (ds, variables);
}


Communication::HiTerm::WriteVariables::Response* Communication::HiTerm::WriteVariables::Response::New (DeserializationSelector ds) const
{
	return new Response (ds);
}


UInt8 Communication::HiTerm::WriteVariables::Response::GetID () const
{
	return WriteVariables::GetID ();
}


UInt16 Communication::HiTerm::WriteVariables::Response::GetLength () const
{
	return 0u;
}


size_t Communication::HiTerm::WriteVariables::Response::ReadData (DataStream& /*ds*/, UInt16 length)
{
	if (length != 0u) {
		TODO; // #TODO_ExceptionHandling
	}

	return 0u;
}


size_t Communication::HiTerm::WriteVariables::Response::WriteData (DataStream& /*ds*/) const
{
	return 0u;
}