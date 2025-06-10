#include "SymbolFile.hpp"

// #Kernel
#include "Types\DataStream.hpp"
#include "Utilities\StringFunctions.hpp"

// #FileHandler
#include "Header\OptionalHeader.hpp"
#include "Header\SectionHeader.hpp"
//#include "SymbolTable\RelocationEntry.hpp"
#include "SymbolTable\SymbolTableEntry.hpp"


ISymbolFile::~ISymbolFile () = default;


//SymbolFile::SymbolFile ()
//	: optionalHeader (nullptr)
//{
//}


File::COFF::SymbolFile::SymbolFile (DeserializationSelector ds, const ByteArray& byteArray)
	: ISymbolFile		(ds)
	, header			(ds)
	, optionalHeader	(nullptr)
	, byteArray			(byteArray)
{
//	TODO; // #TODO_DeleteThisConstructor
}


File::COFF::SymbolFile::~SymbolFile ()
{
	for (const auto& sectionHeader : sectionHeaders) {
		delete sectionHeader;
	}
	for (const auto& symbol : symbols) {
		delete symbol;
	}
}


void File::COFF::SymbolFile::Enumerate (const std::function<void (const SymbolTableEntry&)>& process) const
{
	for (const auto& symbol : symbols) {
		process (*symbol);
	}
}


std::string File::COFF::SymbolFile::GetName (const UInt32 index) const
{
	const auto startIndexOfStrings = header.GetStartAddressOfSymbolTable () + header.GetNumOfEntriesInSymbolTable () * 18u;
	return Utilities::BytesToString (reinterpret_cast<const UInt8*> (byteArray.data () + startIndexOfStrings + index));
}


File::COFF::SymbolConstPtr File::COFF::SymbolFile::GetEntryByIndex (const UInt32 index) const
{
	const auto startIndex = header.GetStartAddressOfSymbolTable () + index * TableEntry::Size ();
	ByteArray symbolArray (byteArray.data () + startIndex, 2u * TableEntry::Size ());
	DataStream symbolStream (symbolArray);
	symbolStream.setByteOrder (DataStream::ByteOrder::LittleEndian);

	SymbolPtr symbol (std::make_shared<SymbolTableEntry> (ForDeserialization));
	symbol->Read (symbolStream);
	return symbol;
}


size_t File::COFF::SymbolFile::Read (DataStream& is)
{
	size_t size = header.Read (is);

	optionalHeader = nullptr;

	if (header.GetSizeOfTheOptionalHeader () != 0u) {
		ASSERT (header.GetSizeOfTheOptionalHeader () == 28u);
		optionalHeader = std::make_unique<OptionalHeader> (ForDeserialization);
		size += optionalHeader->Read (is);
	}

	for (UInt32 i = 0u; i < header.GetNumOfSectionHeaders (); ++i) {
		auto sectionHeader = std::make_unique<SectionHeaderCOFF2> (ForDeserialization);
		size += sectionHeader->Read (is);
		sectionHeaders.push_back (sectionHeader.release ()); // #ToDo: use Owner or vector<SectionHeaderCOFF2> ???

//		const auto physicalAddress = sectionHeader->GetPhysicalAddress ();
//		const auto pointerToRawData = sectionHeader->GetPointerToRawData ();
//		const auto size = sectionHeader->GetSizeInBytes (header.GetTargetID ());
//		ByteArray subArray;
//		for (UInt32 i = 0u; i < size; ++i) {
//			subArray.append (byteArray[pointerToRawData + i]);
//		}
//		subArray.clear ();
//
//		const auto pointerToRelocEntries = sectionHeader->GetPointerToRelocationEntries ();
//		const auto relocSize = sectionHeader->GetNumOfRelocationEntries ();
//		std::vector<RelocationEntry> relocArray;
//		for (UInt32 i = 0u; i < relocSize; ++i) {
//			ByteArray array;
//			for (UInt32 j = 0u; j < 10u; ++j) {
//				array.append (byteArray[pointerToRelocEntries + i]);
//			}
//			DataStream is (array);
//			auto relocEntry = std::make_unique<RelocationEntry> (ForDeserialization);
//			relocEntry->Read (is);
//			array.clear ();
//		}
//		relocArray.clear ();
	}

	const auto startIndex = header.GetStartAddressOfSymbolTable ();
	ByteArray symbolArray (byteArray.data () + startIndex, byteArray.size () - startIndex);
	DataStream symbolStream (symbolArray);
	symbolStream.setByteOrder (DataStream::ByteOrder::LittleEndian);

	for (Int32 i = 0u; i < header.GetNumOfEntriesInSymbolTable (); ++i) {
		auto v = std::make_unique<SymbolTableEntry> (ForDeserialization);
		v->Read (symbolStream);
		if (v->HasAuxiliaryEntry ()) {
			++i;
			ASSERT (i < header.GetNumOfEntriesInSymbolTable ());
		}

		const auto& name = v->GetName (*this);
		if (name == ".text" || name == ".data" || name == ".bss" || name == "etext" || name == "edata" || name == "end") {
			INSPECT (v->HasAuxiliaryEntry (), name.c_str ());
		}

		symbols.push_back (v.release ()); // #ToDo: use Owner or vector<SymbolTableEntry> ???
	}



	return size;
}


size_t File::COFF::SymbolFile::Write (DataStream& os) const
{
	size_t size = header.Write (os);

	if (optionalHeader != nullptr) {
		ASSERT (header.GetSizeOfTheOptionalHeader () == 28u);
		size += optionalHeader->Write (os);
	}

	for (UInt32 i = 0u; header.GetNumOfSectionHeaders (); ++i) {
		size += sectionHeaders[i]->Write (os);
	}

	ASSERT (false);

	return size;
}