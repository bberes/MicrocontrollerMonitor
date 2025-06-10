#pragma once
#ifndef FileHandler__COFF_EntryTypes__hpp
#define FileHandler__COFF_EntryTypes__hpp

// #Standard
#include <memory>


namespace File {
namespace COFF {

	class AuxiliaryEntry;
	class SymbolTableEntry;

	using AuxiliaryConstPtr	= std::shared_ptr<const AuxiliaryEntry>;

	using SymbolPtr			= std::shared_ptr<SymbolTableEntry>;
	using SymbolConstPtr	= std::shared_ptr<const SymbolTableEntry>;

}
}


#endif