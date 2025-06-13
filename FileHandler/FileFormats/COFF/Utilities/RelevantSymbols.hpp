#pragma once
#ifndef FileHandler__COFF_RelevantSymbols__hpp
#define FileHandler__COFF_RelevantSymbols__hpp

// #Standard
#include <functional>
#include <vector>

// #FileHandler
#include "FileFormats\COFF\SymbolTable\SymbolEntry.hpp"
#include "FileHandlerTypes.hpp"


namespace File::COFF {

using SymbolProcessor = std::function<void (const SymbolEntry&)>;


class RelevantSymbols final {
public:
	explicit RelevantSymbols (const SymbolFile& symbolFile);
	~RelevantSymbols ();

	RelevantSymbols (const RelevantSymbols&)					= delete;
	RelevantSymbols&	operator=	(const RelevantSymbols&)	= delete;

	void				Enumerate	(const SymbolProcessor& process) const;

private:
	std::vector<SymbolEntry>	symbols;
//	std::vector<std::string>	names;
};

}


#endif