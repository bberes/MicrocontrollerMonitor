#include "HeaderFlags.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"


namespace {

constexpr uint16_t F_RELFLG		= 0x0001u;	// Relocation information was stripped from the file
constexpr uint16_t F_EXEC		= 0x0002u;	// The file is relocatable (it contains no unresolved external references)
constexpr uint16_t F_LNNO		= 0x0004u;	// For TMS430 and TMS470 only: Line numbers were stripped from the file. For other targets: Reserved
constexpr uint16_t F_LSYMS		= 0x0008u;	// Local symbols were stripped from the file
constexpr uint16_t F_LITTLE		= 0x0100u;	// The target is a little-endian device
constexpr uint16_t F_BIG		= 0x0200u;	// For C6000, MSP430, and TMS470 only: The target is a big-endian device. For other targets: Reserved
constexpr uint16_t F_SYMMERGE	= 0x1000u;	// For C2800, MSP430, and TMS470: Duplicate symbols were removed. For C6000: Reserved

}


File::COFF::HeaderFlags::HeaderFlags (DeserializationSelector ds)
	: Deserializable (ds)
{
}


size_t File::COFF::HeaderFlags::Read (DataStream& is)
{
	const size_t size = ::Read (is, flags);
	DEBUG_ONLY (DebugInit ());
	return size;
}


size_t File::COFF::HeaderFlags::Write (DataStream& os) const
{
	return ::Write (os, flags);
}


bool File::COFF::HeaderFlags::HasRelocationInfo () const
{
	return !(flags & F_RELFLG);
}


bool File::COFF::HeaderFlags::IsRelocatable () const
{
	return flags & F_EXEC;
}


bool File::COFF::HeaderFlags::HasLineNumbers (const TargetID& targetID) const
{
	if (targetID != TargetID::MSP430 && targetID != TargetID::TMS470) {
		TODO; // #TODO_ExceptionHandling
	}
	return !(flags & F_LNNO);
}


bool File::COFF::HeaderFlags::HasLocalSymbols () const
{
	return !(flags & F_LSYMS);
}


bool File::COFF::HeaderFlags::IsLittleEndianDevice () const
{
	return flags & F_LITTLE;
}


bool File::COFF::HeaderFlags::IsBigEndianDevice (const TargetID& targetID) const
{
	if (targetID != TargetID::TMS320C6000 && targetID != TargetID::MSP430 && targetID != TargetID::TMS470) {
		TODO; // #TODO_ExceptionHandling
	}
	return flags & F_BIG;
}


bool File::COFF::HeaderFlags::HasDuplicatedSymbols (const TargetID& targetID) const
{
	if (targetID != TargetID::TMS320C2800 && targetID != TargetID::MSP430 && targetID != TargetID::TMS470) {
		TODO; // #TODO_ExceptionHandling
	}
	return !(flags & F_SYMMERGE);
}


DEBUG_ONLY (
void File::COFF::HeaderFlags::DebugInit ()
{
	hasRelocationInfo		= HasRelocationInfo ();
	isRelocatable			= IsRelocatable ();
	hasLineNumbers			= HasLineNumbers (TargetID::MSP430);
	hasLocalSymbols			= HasLocalSymbols ();
	isLittleEndianDevice	= IsLittleEndianDevice ();
	isBigEndianDevice		= IsBigEndianDevice (TargetID::MSP430);
	hasDuplicatedSymbols	= HasDuplicatedSymbols (TargetID::MSP430);
}
)