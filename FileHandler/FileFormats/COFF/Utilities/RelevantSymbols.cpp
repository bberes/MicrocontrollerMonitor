#include "RelevantSymbols.hpp"

// #FileHandler
#include "FileFormats\COFF\SymbolTable\SymbolTableEntry.hpp"
#include "FileFormats\COFF\SymbolFile.hpp"


namespace {

using namespace File::COFF;


inline bool IsVoidType (const SymbolTableEntry& symbol)
{
	return symbol.GetTypeSpecifier ().GetBaseType () == BaseType::Void;
}


inline bool IsFunctionType (const SymbolTableEntry& symbol)
{
	return symbol.GetTypeSpecifier ().GetFirstDerived () == DerivedType::Function;
}


inline bool IsLocatedInRAM (const SymbolTableEntry& symbol)
{
	if (symbol.GetValue () >= 0x070000u && symbol.GetValue () <= 0x0BFFFFu) {
		return false;
	}
	if (symbol.GetValue () >= 0x3F0000u) {
		return false;
	}
	return true;
}


template <typename... Params>
inline bool Contains (const std::string& string, Params&&... params)
{
	return string.find (std::forward<Params> (params)...) < string.length ();
}

}


File::COFF::RelevantSymbols::RelevantSymbols (const SymbolFile& symbolFile)
{
	UInt32 consyAddress = std::numeric_limits<UInt32>::max ();
	symbolFile.Enumerate ([this, &consyAddress, &symbolFile] (const SymbolTableEntry& symbol) {
		if (IsVoidType (symbol) || IsFunctionType (symbol) ||
			symbol.GetStorageClass () == StorageClass::C_STAT ||
			symbol.GetStorageClass () == StorageClass::C_LABEL ||
			symbol.GetStorageClass () == StorageClass::C_FILE)
		{
			return;
		}

		if (!IsLocatedInRAM (symbol)) {
			return;
		}

		const auto& name = symbol.GetName (symbolFile);
		if (Contains (name, "$$")) {
			return;
		}

		if (name == "_Consy") {
			consyAddress = symbol.GetValue ();
		}

		if (symbol.GetStorageClass () != StorageClass::C_EXT) {
			return;
		}

		symbols.push_back (std::make_shared<SymbolTableEntry> (symbol));
//		names.push_back (name);
	});

	INSPECT (consyAddress < std::numeric_limits<UInt32>::max (), "Why is it important?");
}


File::COFF::RelevantSymbols::~RelevantSymbols () = default;


void File::COFF::RelevantSymbols::Enumerate (const SymbolProcessor& process) const
{
	for (const auto symbol : symbols) {
		process (symbol);
	}
}