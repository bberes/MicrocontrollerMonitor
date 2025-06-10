#include "FileHeader.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"


File::COFF::FileHeader::FileHeader (DeserializationSelector ds)
	: Deserializable	(ds)
	, flags				(ds)
{
}


size_t File::COFF::FileHeader::Read (DataStream& is)
{
	size_t size = 0u;
	size += ::Read (is, versionID);
	size += ::Read (is, numOfSectinoHeaders);
	size += ::Read (is, timeAndDateStamp);
	size += ::Read (is, startAddressOfSymbolTable);
	size += ::Read (is, numOfEntriesInSymbolTable);
	size += ::Read (is, sizeOfTheOptionalHeader);
	size += flags.Read (is);
	size += ::Read (is, targetID);
	return size;
}


size_t File::COFF::FileHeader::Write (DataStream& os) const
{
	size_t size = 0u;
	size += ::Write (os, versionID);
	size += ::Write (os, numOfSectinoHeaders);
	size += ::Write (os, timeAndDateStamp);
	size += ::Write (os, startAddressOfSymbolTable);
	size += ::Write (os, numOfEntriesInSymbolTable);
	size += ::Write (os, sizeOfTheOptionalHeader);
	size += flags.Write (os);
	size += ::Write (os, targetID);
	return size;
}


UInt16 File::COFF::FileHeader::GetNumOfSectionHeaders () const
{
	return numOfSectinoHeaders;
}


Int32 File::COFF::FileHeader::GetStartAddressOfSymbolTable () const
{
	return startAddressOfSymbolTable;
}


Int32 File::COFF::FileHeader::GetNumOfEntriesInSymbolTable () const
{
	return numOfEntriesInSymbolTable;
}


UInt16 File::COFF::FileHeader::GetSizeOfTheOptionalHeader () const
{
	return sizeOfTheOptionalHeader;
}


File::COFF::TargetID File::COFF::FileHeader::GetTargetID () const
{
	return TargetID (targetID);
}