#include "CommonParts.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"

// #Communication
#include "Protocols\HiTerm\CommandData\HiTermVariable.hpp"


size_t Communication::HiTerm::LengthOf (const Vector<Variable>& variables)
{
	size_t size = 0u;
	for (auto& variable : variables) {
		size += variable.GetSize ();
	}
	return size;
}


size_t Communication::HiTerm::Read (DataStream& ds, Vector<Variable>& variables, UInt16 length)
{
	variables.clear ();
	size_t size = 0u;
	for ( ; size < length; ) {
		Variable variable (ForDeserialization);
		size += variable.Read (ds);
		if (size > length) {
			TODO; // #TODO_ExceptionHandling
		}
		variables.push_back (variable);
	}
	return size;
}


size_t Communication::HiTerm::Write (DataStream& ds, const Vector<Variable>& variables)
{
	size_t size = 0u;
	for (auto& variable : variables) {
		size += variable.Write (ds);
	}
	return size;
}


using Communication::HiTerm::Memory;


static Memory ConvertFromOld (const Memory& memory)
{
	switch (memory.GetMemSize ()) {
	case Memory::Size::_1_Byte__: return Memory (memory.GetAddress (), Memory::Size::_2_Bytes_);
	case Memory::Size::_2_Bytes_: return Memory (memory.GetAddress (), Memory::Size::_4_Bytes_);
	default: TODO; // #ToDo
	}
}


size_t Communication::HiTerm::Deprecated::ReadOld (DataStream& ds, MemoryEntries& memoryEntries, UInt16 length)
{
	memoryEntries.clear ();
	size_t size = 0u;
	for ( ; size < length; ) {
		Memory memory (ForDeserialization);
		size += memory.Read (ds);
		if (size > length) {
			TODO; // #TODO_ExceptionHandling
		}
		memoryEntries.push_back (ConvertFromOld (memory));
	}
	return size;
}


static Memory ConvertToOld (const Memory& memory)
{
	switch (memory.GetMemSize ()) {
	case Memory::Size::_2_Bytes_: return Memory (memory.GetAddress (), Memory::Size::_1_Byte__);
	case Memory::Size::_4_Bytes_: return Memory (memory.GetAddress (), Memory::Size::_2_Bytes_);
	default: TODO; // #ToDo
	}
}


size_t Communication::HiTerm::Deprecated::WriteOld (DataStream& ds, const MemoryEntries& memoryEntries)
{
	size_t size = 0u;
	for (auto& memory : memoryEntries) {
		size += ConvertToOld (memory).Write (ds);
	}
	return size;
}


using Communication::HiTerm::Variable;


static size_t ReadVariableOld (DataStream& is, Variable& variable)
{
	Memory memory (ForDeserialization);
	size_t size = memory.Read (is);

	memory = ConvertFromOld (memory);

	if (memory.GetMemSize () == Memory::Size::_2_Bytes_) {
		UInt16 v16 = 0u;
		size += ::Read (is, v16, ByteOrder::MSBFirst);
		variable = Variable (memory.GetAddress (), v16);
		return size;
	}

	if (memory.GetMemSize () == Memory::Size::_4_Bytes_) {
		UInt32 v32 = 0u;
		size += ::Read (is, v32, ByteOrder::MSBFirst);
		variable = Variable (memory.GetAddress (), v32);
		return size;
	}

	TODO; // #ToDo
}


size_t Communication::HiTerm::Deprecated::ReadOld (DataStream& ds, Variables& variables, UInt16 length)
{
	variables.clear ();
	size_t size = 0u;
	for ( ; size < length; ) {
		Variable variable (ForDeserialization);
		size += ReadVariableOld (ds, variable);
		if (size > length) {
			TODO; // #TODO_ExceptionHandling
		}
		variables.push_back (variable);
	}
	return size;
}


static size_t WriteVariableOld (DataStream& os, const Variable& variable)
{
	const Memory& memory = variable.GetMemory ();
	size_t size = ConvertToOld (memory).Write (os);
	switch (memory.GetMemSize ()) {
	case Memory::Size::_2_Bytes_: size += ::Write (os, variable.GetValue<UInt16> (), ByteOrder::MSBFirst); break;
	case Memory::Size::_4_Bytes_: size += ::Write (os, variable.GetValue<UInt32> (), ByteOrder::MSBFirst); break;
	default: TODO; // #ToDo
	}
	return size;
}


size_t Communication::HiTerm::Deprecated::WriteOld (DataStream& ds, const Variables& variables)
{
	size_t size = 0u;
	for (auto& variable : variables) {
		size += WriteVariableOld (ds, variable);
	}
	return size;
}