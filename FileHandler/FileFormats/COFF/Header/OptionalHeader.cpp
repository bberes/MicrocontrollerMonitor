#include "OptionalHeader.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"


File::COFF::OptionalHeader::OptionalHeader (DeserializationSelector ds)
	: Deserializable (ds)
{
}


size_t File::COFF::OptionalHeader::Read (DataStream& is)
{
	size_t size = 0u;
	size += ::Read (is, optionalFileHeaderNum);
	size += ::Read (is, versionStamp);
	size += ::Read (is, sizeOfExecutableCode);
	size += ::Read (is, sizeOfInitializedData);
	size += ::Read (is, sizeOfUninitializedData);
	size += ::Read (is, entryPoint);
	size += ::Read (is, startAddressOfExecutableData);
	size += ::Read (is, startAddressOfInitializedData);

	ASSERT (optionalFileHeaderNum == 0x0108);

	return size;
}


size_t File::COFF::OptionalHeader::Write (DataStream& os) const
{
	size_t size = 0u;
	size += ::Write (os, optionalFileHeaderNum);
	size += ::Write (os, versionStamp);
	size += ::Write (os, sizeOfExecutableCode);
	size += ::Write (os, sizeOfInitializedData);
	size += ::Write (os, sizeOfUninitializedData);
	size += ::Write (os, entryPoint);
	size += ::Write (os, startAddressOfExecutableData);
	size += ::Write (os, startAddressOfInitializedData);
	return size;
}