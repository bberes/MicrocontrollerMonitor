#include "WriteVariables_DEPRECATED.hpp"

// #Kernel
#include "Utilities\Debug.hpp"
#include "Utilities\Memory.hpp"

// #Communication
#include "Protocols\HiTerm\Utilities\CommonParts.hpp"
#include "Protocols\HiTerm\HiTermCommandIDs.hpp"


UInt8 Communication::HiTerm::Deprecated::WriteVariables::GetID ()
{
	return HiTerm::CommandID::WRITE;
}


Communication::HiTerm::Deprecated::WriteVariables::Command::Command (DeserializationSelector ds)
	: CommandBase (ds)
{
}


Communication::HiTerm::Deprecated::WriteVariables::Command::Command (UInt8 key, const Variables& variables)
	: CommandBase	(key)
	, variables		(variables)
{
}


Communication::HiTerm::Deprecated::WriteVariables::Command* Communication::HiTerm::Deprecated::WriteVariables::Command::New (DeserializationSelector ds) const
{
	return MakeRaw<Command> (ds);
}


UInt8 Communication::HiTerm::Deprecated::WriteVariables::Command::GetID () const
{
	return WriteVariables::GetID ();
}


UInt16 Communication::HiTerm::Deprecated::WriteVariables::Command::GetLength () const
{
	return static_cast<UInt16> (LengthOf (variables));
}


size_t Communication::HiTerm::Deprecated::WriteVariables::Command::ReadData (DataStream& ds, UInt16 length)
{
	return ReadOld (ds, variables, length);
}


size_t Communication::HiTerm::Deprecated::WriteVariables::Command::WriteData (DataStream& ds) const
{
	return WriteOld (ds, variables);
}


Communication::HiTerm::Deprecated::WriteVariables::Response* Communication::HiTerm::Deprecated::WriteVariables::Response::New (DeserializationSelector ds) const
{
	return MakeRaw<Response> (ds);
}


UInt8 Communication::HiTerm::Deprecated::WriteVariables::Response::GetID () const
{
	return WriteVariables::GetID ();
}


UInt16 Communication::HiTerm::Deprecated::WriteVariables::Response::GetLength () const
{
	return 0u;
}


size_t Communication::HiTerm::Deprecated::WriteVariables::Response::ReadData (DataStream& /*ds*/, UInt16 length)
{
	if (length != 0u) {
		TODO; // #TODO_ExceptionHandling
	}

	return 0u;
}


size_t Communication::HiTerm::Deprecated::WriteVariables::Response::WriteData (DataStream& /*ds*/) const
{
	return 0u;
}