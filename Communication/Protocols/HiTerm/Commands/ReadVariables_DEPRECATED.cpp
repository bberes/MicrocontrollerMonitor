#include "ReadVariables_DEPRECATED.hpp"

// #Kernel
#include "Utilities\Debug.hpp"

// #Communication
#include "Protocols\HiTerm\Utilities\CommonParts.hpp"
#include "Protocols\HiTerm\HiTermCommandIDs.hpp"


// +--------------------------------------------------------------------------+
// | Command ReadVariables                                                    |
// |  In field Data the Master describes the address and size in sequence for |
// |  every requested variable. Address is 4 bytes, size description is 1     |
// |  byte. Thus the field Length is equal to (4 + 1) * number of requested   |
// |  variables.                                                              |
// |  The answer (sent by the Slave) to this command contains the address and |
// |  size fields extended with the value of the requested variable in        |
// |  sequence for every requested variable.                                  |
// | !!! WARNING !!! RESTRICTION !!!                                          |
// |  This command supports only variables with size 2 and 4 bytes and these  |
// |  values are represented by 1 and 2 respectively.                         |
// +--------------------------------------------------------------------------+


UInt8 Communication::HiTerm::Deprecated::ReadVariables::GetID ()
{
	return HiTerm::CommandID::READ;
}


Communication::HiTerm::Deprecated::ReadVariables::Command::Command (DeserializationSelector ds)
	: CommandBase (ds)
{
}


Communication::HiTerm::Deprecated::ReadVariables::Command::Command (UInt8 key, const MemoryEntries& memoryEntries)
	: CommandBase	(key)
	, memoryEntries	(memoryEntries)
{
}


Communication::HiTerm::Deprecated::ReadVariables::Command* Communication::HiTerm::Deprecated::ReadVariables::Command::New (DeserializationSelector ds) const
{
	return new Command (ds);
}


UInt8 Communication::HiTerm::Deprecated::ReadVariables::Command::GetID () const
{
	return ReadVariables::GetID ();
}


UInt16 Communication::HiTerm::Deprecated::ReadVariables::Command::GetLength () const
{
	return static_cast<UInt16> (Memory::GetSize () * memoryEntries.size ());
}


size_t Communication::HiTerm::Deprecated::ReadVariables::Command::ReadData (DataStream& ds, UInt16 length)
{
	return ReadOld (ds, memoryEntries, length);
}


size_t Communication::HiTerm::Deprecated::ReadVariables::Command::WriteData (DataStream& ds) const
{
	return WriteOld (ds, memoryEntries);
}


Communication::HiTerm::Deprecated::ReadVariables::Response::Response (DeserializationSelector ds)
	: ResponseBase (ds)
{
}


Communication::HiTerm::Deprecated::ReadVariables::Response::Response (UInt8 key, const Variables& variables)
	: ResponseBase	(key)
	, variables		(variables)
{
}


Communication::HiTerm::Deprecated::ReadVariables::Response* Communication::HiTerm::Deprecated::ReadVariables::Response::New (DeserializationSelector ds) const
{
	return new Response (ds);
}


UInt8 Communication::HiTerm::Deprecated::ReadVariables::Response::GetID () const
{
	return ReadVariables::GetID ();
}


UInt16 Communication::HiTerm::Deprecated::ReadVariables::Response::GetLength () const
{
	return static_cast<UInt16> (LengthOf (variables));
}


size_t Communication::HiTerm::Deprecated::ReadVariables::Response::ReadData (DataStream& ds, UInt16 length)
{
	return ReadOld (ds, variables, length);
}


size_t Communication::HiTerm::Deprecated::ReadVariables::Response::WriteData (DataStream& ds) const
{
	return WriteOld (ds, variables);
}