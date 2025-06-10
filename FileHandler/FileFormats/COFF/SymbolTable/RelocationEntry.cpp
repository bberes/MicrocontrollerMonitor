#include "RelocationEntry.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"


File::COFF::RelocationEntry::RelocationEntry (DeserializationSelector ds)
	: Deserializable (ds)
{
}


size_t File::COFF::RelocationEntry::Read (DataStream& is)
{
	UInt16 reserved = 0u;
	size_t size = 0u;
	size += ::Read (is, virtualAddress);
	size += ::Read (is, symbolTableIndex);
	size += ::Read (is, reserved);
	ASSERT (reserved == 0u, "It is unused. If its value is not 0, then its role needs investigation.");
	size += ::Read (is, relocationType);
	return size;
}


size_t File::COFF::RelocationEntry::Write (DataStream& os) const
{
	const UInt16 reserved = 0u;
	size_t size = 0u;
	size += ::Write (os, virtualAddress);
	size += ::Write (os, symbolTableIndex);
	size += ::Write (os, reserved);
	size += ::Write (os, relocationType);
	return size;
}