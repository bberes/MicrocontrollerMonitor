#pragma once
#ifndef FileHandler__COFF_EntryTypes__hpp
#define FileHandler__COFF_EntryTypes__hpp

// #Standard
#include <memory>


namespace File {
namespace COFF {

	class AuxEntry;
	class SymbolEntry;

	using AuxiliaryConstPtr	= std::shared_ptr<const AuxEntry>;

	using SymbolConstPtr	= std::shared_ptr<const SymbolEntry>;

}
}


#endif