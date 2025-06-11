#include "ReadVariables.hpp"

// #Kernel
#include "Utilities\Debug.hpp"
#include "Utilities\Memory.hpp"

// #Communication
#include "Protocols\HiTerm\Utilities\CommonParts.hpp"
#include "Protocols\HiTerm\HiTermCommandIDs.hpp"


UInt8 Communication::HiTerm::ReadVariables::GetID ()
{
	return HiTerm::CommandID::READ_NEW;
}


Communication::HiTerm::ReadVariables::Command::Command (DeserializationSelector ds)
	: CommandBase (ds)
{
}


Communication::HiTerm::ReadVariables::Command::Command (UInt8 key, const MemoryEntries& memoryEntries)
	: CommandBase	(key)
	, memoryEntries	(memoryEntries)
{
}


Communication::HiTerm::ReadVariables::Command* Communication::HiTerm::ReadVariables::Command::New (DeserializationSelector ds) const
{
	return MakeRaw<Command> (ds);
}


UInt8 Communication::HiTerm::ReadVariables::Command::GetID () const
{
	return ReadVariables::GetID ();
}


UInt16 Communication::HiTerm::ReadVariables::Command::GetLength () const
{
	return static_cast<UInt16> (Memory::GetSize () * memoryEntries.size ());
}


size_t Communication::HiTerm::ReadVariables::Command::ReadData (DataStream& ds, UInt16 length)
{
	memoryEntries.clear ();
	size_t size = 0u;
	for ( ; size < length; ) {
		Memory memory (ForDeserialization);
		size += memory.Read (ds);
		if (size > length) {
			TODO; // #TODO_ExceptionHandling
		}
		memoryEntries.push_back (memory);
	}
	return size;
}


size_t Communication::HiTerm::ReadVariables::Command::WriteData (DataStream& ds) const
{
	size_t size = 0u;
	for (auto& memory : memoryEntries) {
		size += memory.Write (ds);
	}
	return size;
}


Communication::HiTerm::ReadVariables::Response::Response (DeserializationSelector ds)
	: ResponseBase (ds)
{
}


Communication::HiTerm::ReadVariables::Response::Response (UInt8 key, const Variables& variables)
	: ResponseBase	(key)
	, variables		(variables)
{
}


Communication::HiTerm::ReadVariables::Response* Communication::HiTerm::ReadVariables::Response::New (DeserializationSelector ds) const
{
	return MakeRaw<Response> (ds);
}


UInt8 Communication::HiTerm::ReadVariables::Response::GetID () const
{
	return ReadVariables::GetID ();
}


UInt16 Communication::HiTerm::ReadVariables::Response::GetLength () const
{
	return static_cast<UInt16> (LengthOf (variables));
}


size_t Communication::HiTerm::ReadVariables::Response::ReadData (DataStream& ds, UInt16 length)
{
	return ::Communication::HiTerm::Read (ds, variables, length);
}


size_t Communication::HiTerm::ReadVariables::Response::WriteData (DataStream& ds) const
{
	return ::Communication::HiTerm::Write (ds, variables);
}