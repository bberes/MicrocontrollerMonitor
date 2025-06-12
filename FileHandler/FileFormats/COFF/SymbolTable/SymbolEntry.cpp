#include "SymbolEntry.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"
#include "Utilities\StringFunctions.hpp"

// #FileHandler
#include "FileFormats\COFF\SymbolFile.hpp"
#include "AuxiliaryEntry.hpp"


File::COFF::SymbolEntry::SymbolEntry (DeserializationSelector ds)
	: TableEntry		(ds)
	, auxiliaryEntry	(nullptr)
{
}


File::COFF::SymbolEntry::~SymbolEntry () = default;


std::string File::COFF::SymbolEntry::GetName (const SymbolFile& symbolFile) const
{
	if (symbolName[0] == '\0') {
		ASSERT (symbolName[1] == '\0' && symbolName[2] == '\0' && symbolName[3] == '\0');
		const auto address = *reinterpret_cast<const UInt32*> (&symbolName[4]);
		if (address != 0) {
			return symbolFile.GetName (address);
		}
	}
	return Utilities::BytesToString (symbolName, 8u);
}


EntryType File::COFF::SymbolEntry::GetType () const
{
	return EntryType::Symbol;
}


size_t File::COFF::SymbolEntry::Read (DataStream& is)
{
	size_t size = 0u;

	for (UInt32 i = 0u; i < 8u; ++i) {
		size += ::Read (is, symbolName[i]);
	}

	size += ::Read (is, symbolValue);
	size += ::Read (is, sectionNumber);
	size += ::Read (is, reserved);

	UInt8 storageClass = 0u;
	size += ::Read (is, storageClass);
	this->storageClass = static_cast<StorageClass> (storageClass);
	
	size += ::Read (is, numOfAuxiliaryEntries);

	auxiliaryEntry = nullptr;

	if (numOfAuxiliaryEntries != 0u) {
//		Q_ASSERT (numOfAuxiliaryEntries == 1u);
		auto auxEntryNotConst = std::make_shared<AuxEntry> (ForDeserialization);
		size += auxEntryNotConst->Read (is);
		auxiliaryEntry = auxEntryNotConst;
	}

	return size;
}


size_t File::COFF::SymbolEntry::Write (DataStream& os) const
{
	size_t size = 0u;

	for (UInt32 i = 0u; i < 8u; ++i) {
		size += ::Write (os, symbolName[i]);
	}
	
	size += ::Write (os, symbolValue);
	size += ::Write (os, sectionNumber);
	size += ::Write (os, reserved);
	
	size += ::Write (os, static_cast<UInt8> (storageClass));
	
	size += ::Write (os, numOfAuxiliaryEntries);

	if (numOfAuxiliaryEntries != 0) {
		ASSERT (numOfAuxiliaryEntries == 1u);
		ASSERT (auxiliaryEntry != nullptr);
		size += auxiliaryEntry->Write (os);
	}

	return size;
}