#include "AuxiliaryEntry.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"
#include "Utilities\TypeTraits.hpp"


File::COFF::AuxEntry::AuxEntry (DeserializationSelector ds)
	: TableEntry (ds)
{
}


void File::COFF::AuxEntry::DecreaseDimension ()
{
	ASSERT (IsMultidimensional ());

	const UInt16 dim0 = GetArrayDimensionSize ();
	ASSERT (dim0 > 0u);

	ASSERT (numOfRelocationEntries % dim0 == 0u);
	numOfRelocationEntries /= dim0;
	ASSERT (numOfRelocationEntries % 16u == 0u);

	INSPECT (numOfLineNumberEntries == 0u);

	UInt8 buffer[8];
	static_assert (sizeof (buffer) == 8u);
	std::memcpy (buffer, &notUsed[2], sizeof (buffer));
	std::memcpy (notUsed, buffer, sizeof (buffer));
	notUsed[8] = 0u;
	notUsed[9] = 0u;
}


bool File::COFF::AuxEntry::IsMultidimensional () const
{
	return GetArrayDimensionSize (1u) > 0u;
}


UInt16 File::COFF::AuxEntry::GetArrayDimensionSize (size_t dimIndex/* = 0u*/) const
{
	ASSERT (dimIndex < 5u);
	return InterpretAs<UInt16> (notUsed, dimIndex);
}


EntryType File::COFF::AuxEntry::GetType () const
{
	return EntryType::Auxiliary;
}


size_t File::COFF::AuxEntry::Read (DataStream& is)
{
	size_t size = 0u;

	size += ::Read (is, sectionLength);
	size += ::Read (is, numOfRelocationEntries);
	size += ::Read (is, numOfLineNumberEntries);

	for (UInt32 i = 0u; i < 10u; ++i) {
		size += ::Read (is, notUsed[i]);
		if (notUsed[i] != 0u) {
			continue;
		}
//		ASSERT (notUsed[i] == 0u);
	}

	return size;
}


size_t File::COFF::AuxEntry::Write (DataStream& os) const
{
	size_t size = 0u;

	size += ::Write (os, sectionLength);
	size += ::Write (os, numOfRelocationEntries);
	size += ::Write (os, numOfLineNumberEntries);

	for (UInt32 i = 0u; i < 10u; ++i) {
		size += ::Write (os, notUsed[i]);
	}

	return size;
}