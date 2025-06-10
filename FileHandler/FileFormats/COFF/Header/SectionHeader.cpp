#include "SectionHeader.hpp"

// #Standard
#include <stdexcept>

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"
#include "Utilities\StringFunctions.hpp"


File::COFF::SectionHeaderBase::SectionHeaderBase (DeserializationSelector ds)
	: Deserializable (ds)
{
}


size_t File::COFF::SectionHeaderBase::Read (DataStream& is)
{
	size_t size = 0u;
	for (UInt32 i = 0u; i < 8u; ++i) {
		size += ::Read (is, sectionNameOrPointer[i]);
	}

	size += ::Read (is, physicalAddress);
	size += ::Read (is, virtualAddress);
	size += ::Read (is, sizeInBytesOrWords);
	size += ::Read (is, pointerToRawData);
	size += ::Read (is, pointerToRelocationEntries);
	size += ::Read (is, reserved_1);
	INSPECT (reserved_1 == 0u, "It is unused. If its value is not 0, then its role needs investigation.");

	size += ReadImpl (is);

	return size;
}


size_t File::COFF::SectionHeaderBase::Write (DataStream& os) const
{
	size_t size = 0u;
	for (UInt32 i = 0u; i < 8u; ++i) {
		size += ::Write (os, sectionNameOrPointer[i]);
	}

	size += ::Write (os, physicalAddress);
	size += ::Write (os, virtualAddress);
	size += ::Write (os, sizeInBytesOrWords);
	size += ::Write (os, pointerToRawData);
	size += ::Write (os, pointerToRelocationEntries);
	size += ::Write (os, reserved_1);

	size += WriteImpl (os);

	return size;
}


Int32 File::COFF::SectionHeaderBase::GetPhysicalAddress () const
{
	return physicalAddress;
}


Int32 File::COFF::SectionHeaderBase::GetPointerToRawData () const
{
	return pointerToRawData;
}


Int32 File::COFF::SectionHeaderBase::GetPointerToRelocationEntries () const
{
	return pointerToRelocationEntries;
}


Int32 File::COFF::SectionHeaderBase::GetNumOfRelocationEntries () const
{
	return numOfRelocationEntries;
}


UInt32 File::COFF::SectionHeaderBase::GetAlignment (const TargetID& targetID) const
{
	if (targetID == TargetID::MSP430 || targetID == TargetID::TMS470) {
//		For MSP430 and TMS470, alignment is indicated by the bits masked by 0xF00. Alignment is the value in
//		the bits raised to a power equal to the bit value. Alignment is 2 raised to the same power. For example, if
//		the value in these 4 bits is 2, the alignment is 2 raised to the power 2 (or 4)
		TODO; // #TODO_ExceptionHandling
	}
	return (1u << ((static_cast<UInt16> (flags) & 0x0F00u) >> 8));
}


File::COFF::SectionHeaderCOFF1::SectionHeaderCOFF1 (DeserializationSelector ds)
	: SectionHeaderBase (ds)
{
}


std::string File::COFF::SectionHeaderCOFF1::GetSectionName (const SymbolFile& symbolFile) const
{
	ASSERT (sectionNameOrPointer[0] != '\0');
	return Utilities::BytesToString (sectionNameOrPointer, 8u);
}


Int32 File::COFF::SectionHeaderCOFF1::GetSizeInBytes (const TargetID& /*targetID*/) const
{
	return sizeInBytesOrWords << 1;
}


size_t File::COFF::SectionHeaderCOFF1::ReadImpl (DataStream& is)
{
	size_t size = 0u;

	UInt16 numOfRelocationEntries = 0u;
	size += ::Read (is, numOfRelocationEntries);
	this->numOfRelocationEntries = numOfRelocationEntries;

	UInt16 reserved = 0u;
	size += ::Read (is, reserved);
	numOfLineNumberEntries = reserved;

	UInt16 flags;
	size += ::Read (is, flags);
	this->flags = static_cast<SectionFlags> (flags);

	UInt8 reserved_2 = 0u;
	size += ::Read (is, reserved_2);
	this->reserved_2 = reserved_2;
	ASSERT (reserved_2 == 0u, "It is unused. If its value is not 0, then its role needs investigation.");

	UInt8 memoryPageNumber;
	size += ::Read (is, memoryPageNumber);
	this->memoryPageNumber = memoryPageNumber;

	return size;
}


size_t File::COFF::SectionHeaderCOFF1::WriteImpl (DataStream& os) const
{
	size_t size = 0u;

	ASSERT (this->numOfRelocationEntries <= std::numeric_limits<UInt16>::max ());
	const UInt16 numOfRelocationEntries = static_cast<UInt16> (this->numOfRelocationEntries);
	size += ::Write (os, numOfRelocationEntries);

	ASSERT (numOfLineNumberEntries <= std::numeric_limits<UInt16>::max ());
	const UInt16 reserved = static_cast<UInt16> (numOfLineNumberEntries);
	size += ::Write (os, reserved);

	ASSERT (static_cast<UInt32> (flags) <= std::numeric_limits<UInt16>::max ());
	size += ::Write (os, static_cast<UInt16> (flags));

	ASSERT (this->reserved_2 <= std::numeric_limits<UInt8>::max ());
	const UInt8 reserved_2 = static_cast<UInt8> (this->reserved_2);
	size += ::Write (os, reserved_2);

	ASSERT (this->memoryPageNumber <= std::numeric_limits<UInt8>::max ());
	const UInt8 memoryPageNumber = static_cast<UInt8> (this->memoryPageNumber);
	size += ::Write (os, memoryPageNumber);

	return size;
}


File::COFF::SectionHeaderCOFF2::SectionHeaderCOFF2 (DeserializationSelector ds)
	: SectionHeaderBase (ds)
{
}


std::string File::COFF::SectionHeaderCOFF2::GetSectionName (const SymbolFile& symbolFile) const
{
	TODO; // #TODO_Implement ?
}


Int32 File::COFF::SectionHeaderCOFF2::GetSizeInBytes (const TargetID& targetID) const
{
	switch (targetID) {
	case TargetID::TMS320C6000:
	case TargetID::TMS320C5500:
	case TargetID::TMS320C5500Plus:
	case TargetID::TMS470:
	case TargetID::MSP430:
		return sizeInBytesOrWords;
	case TargetID::TMS320C2800:
	case TargetID::TMS320C5400:
		return sizeInBytesOrWords << 1;
	default:
		throw std::invalid_argument ("{2C168175-D62A-402D-B84A-420676805CDD}");
	}
}


size_t File::COFF::SectionHeaderCOFF2::ReadImpl (DataStream& is)
{
	size_t size = 0u;

	size += ::Read (is, numOfRelocationEntries);
	size += ::Read (is, numOfLineNumberEntries);

	UInt32 flags;
	size += ::Read (is, flags);
	this->flags = static_cast<SectionFlags> (flags);

	size += ::Read (is, reserved_2);
	INSPECT (reserved_2 == 0u, "It is unused. If its value is not 0, then its role needs investigation.");

	size += ::Read (is, memoryPageNumber);

	return size;
}


size_t File::COFF::SectionHeaderCOFF2::WriteImpl (DataStream& os) const
{
	size_t size = 0u;

	size += ::Write (os, numOfRelocationEntries);
	size += ::Write (os, numOfLineNumberEntries);

	size += ::Write (os, static_cast<UInt32> (flags));

	size += ::Write (os, reserved_2);

	size += ::Write (os, memoryPageNumber);
		
	return size;
}