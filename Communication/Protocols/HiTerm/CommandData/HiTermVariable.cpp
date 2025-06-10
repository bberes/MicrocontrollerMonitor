#include "HiTermVariable.hpp"

// #Standard
#include <stdexcept>

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"

// #Communication
#include "Data\Variable.hpp"


Communication::HiTerm::Memory::Memory (DeserializationSelector ds)
	: Deserializable (ds)
{
}


namespace {

void Check (Communication::HiTerm::Memory::Size memorySize)
{
	switch (memorySize) {
	case Communication::HiTerm::Memory::Size::_1_Byte__:
	case Communication::HiTerm::Memory::Size::_2_Bytes_:
	case Communication::HiTerm::Memory::Size::_4_Bytes_:
	case Communication::HiTerm::Memory::Size::_8_Bytes_:
		break;
	default:
		TODO; // #TODO_ExceptionHandling
	}
}


void Check (size_t size)
{
	static_assert (Communication::HiTerm::Memory::GetSize () == 5u);
	if (5u != size) {
		TODO; // #TODO_ExceptionHandling
	}
}

}


Communication::HiTerm::Memory::Memory (UInt32 address, Size memorySize)
	: Deserializable	(RegularConstructor)
	, address			(address)
	, memorySize		(memorySize)
{
	Check (memorySize);
}


size_t Communication::HiTerm::Memory::Read (DataStream& is)
{
	size_t size = 0u;
	size += ::Read (is, address, ByteOrder::MSBFirst);
	size += ::Read (is, memorySize);

	Check (memorySize);
	Check (size);

	return size;
}


size_t Communication::HiTerm::Memory::Write (DataStream& os) const
{
	size_t size = 0u;
	size += ::Write (os, address, ByteOrder::MSBFirst);
	size += ::Write (os, memorySize);

	Check (size);

	return size;
}


Communication::HiTerm::Memory::Size Communication::HiTerm::Memory::GetMemSize () const
{
	return memorySize;
}


Communication::HiTerm::Variable::Variable (DeserializationSelector ds)
	: Deserializable	(ds)
	, memory			(ds)
{
}


static UInt64 ValueToUInt64 (const Communication::Variable& v)
{
	const Communication::VariableSize size = v.GetInfo ().GetVariableSize ();
	switch (size) {
	case Communication::VariableSize::Size1Byte : return v.GetValue<UInt8>  ();
	case Communication::VariableSize::Size2Bytes: return v.GetValue<UInt16> ();
	case Communication::VariableSize::Size4Bytes: return v.GetValue<UInt32> ();
	case Communication::VariableSize::Size8Bytes: return v.GetValue<UInt64> ();
	default: throw std::invalid_argument ("{4EB8E4FC-190B-4DE2-8CD3-07653397517E}");
	}
}


static UInt32 AddressToUInt32 (const Communication::MemoryRef& info)
{
	switch (info.GetAddressSize ()) {
	case Communication::AddressSize::Size1Byte : TODO; // #ToDo: HiTerm address is 4 bytes
	case Communication::AddressSize::Size2Bytes: TODO; // #ToDo: warning or abort in these cases?
	case Communication::AddressSize::Size4Bytes: return info.GetAddress<UInt32> ();
	case Communication::AddressSize::Size8Bytes: TODO; // #ToDo: Size8Bytes is incompatible
	default: TODO; // #ToDo: otherwise invalid arg (use at least 2 different exceptions?)
	}
}


static Communication::HiTerm::Memory::Size ToHiTermMemorySize (Communication::VariableSize size)
{
	switch (size) {
	case Communication::VariableSize::Size1Byte : return Communication::HiTerm::Memory::Size::_1_Byte__;
	case Communication::VariableSize::Size2Bytes: return Communication::HiTerm::Memory::Size::_2_Bytes_;
	case Communication::VariableSize::Size4Bytes: return Communication::HiTerm::Memory::Size::_4_Bytes_;
	case Communication::VariableSize::Size8Bytes: return Communication::HiTerm::Memory::Size::_8_Bytes_;
	default: throw std::invalid_argument ("{81C38FB0-698D-4EA2-8D65-FD7D5C8B5B04}");
	}
}


static Communication::HiTerm::Memory ToHiTermMemory (const Communication::MemoryRef& info)
{
	auto address = AddressToUInt32 (info);
	auto memSize = ToHiTermMemorySize (info.GetVariableSize ());
	return Communication::HiTerm::Memory (address, memSize);
}


Communication::HiTerm::Variable::Variable (const Communication::Variable& variable)
	: Deserializable	(RegularConstructor)
	, value				(ValueToUInt64 (variable))
	, memory			(ToHiTermMemory (variable.GetInfo ()))
{
}


size_t Communication::HiTerm::Variable::Read (DataStream& is)
{
	value = 0u;
	size_t size = memory.Read (is);
	switch (memory.GetMemSize ()) {
	case Memory::_1_Byte__:
		size += ::Read (is, reinterpret_cast<UInt8&> (value), ByteOrder::MSBFirst);
		break;
	case Memory::_2_Bytes_:
		size += ::Read (is, reinterpret_cast<UInt16&> (value), ByteOrder::MSBFirst);
		break;
	case Memory::_4_Bytes_:
		size += ::Read (is, reinterpret_cast<UInt32&> (value), ByteOrder::MSBFirst);
		break;
	case Memory::_8_Bytes_:
		size += ::Read (is, value, ByteOrder::MSBFirst);
		break;
	}
	return size;
}


size_t Communication::HiTerm::Variable::Write (DataStream& os) const
{
	size_t size = memory.Write (os);
	switch (memory.GetMemSize ()) {
	case Memory::_1_Byte__:
		size += ::Write (os, static_cast<UInt8> (value), ByteOrder::MSBFirst);
		break;
	case Memory::_2_Bytes_:
		size += ::Write (os, static_cast<UInt16> (value), ByteOrder::MSBFirst);
		break;
	case Memory::_4_Bytes_:
		size += ::Write (os, static_cast<UInt32> (value), ByteOrder::MSBFirst);
		break;
	case Memory::_8_Bytes_:
		size += ::Write (os, static_cast<UInt64> (value), ByteOrder::MSBFirst);
		break;
	}
	return size;
}


void Communication::HiTerm::Variable::CheckSize (size_t size) const
{
	if (memory.GetMemSize () != size) {
		TODO; // #TODO_ExceptionHandling
	}
}


Communication::HiTerm::Variable::operator Communication::Variable () const
{
	const UInt32& address = memory.GetAddress ();
	switch (memory.GetMemSize ()) {
	case Memory::Size::_1_Byte__:	return Communication::Variable (GetValue<UInt8>  (), address);
	case Memory::Size::_2_Bytes_:	return Communication::Variable (GetValue<UInt16> (), address);
	case Memory::Size::_4_Bytes_:	return Communication::Variable (GetValue<UInt32> (), address);
	case Memory::Size::_8_Bytes_:	return Communication::Variable (GetValue<UInt64> (), address);
	}
	TODO; // #TODO
}


size_t Communication::HiTerm::Variable::GetSize () const
{
	return memory.GetSize () + memory.GetMemSize ();
}