#pragma once
#ifndef FileHandler__COFF_RelevantSymbols__hpp
#define FileHandler__COFF_RelevantSymbols__hpp

// #Standard
#include <functional>
#include <vector>

// #FileHandler
#include "FileFormats\COFF\Types\EntryTypes.hpp"
#include "FileHandlerTypes.hpp"


namespace File {
namespace COFF {

using SymbolProcessor = std::function<void (const SymbolPtr&)>;


class RelevantSymbols final {
public:
	explicit RelevantSymbols (const SymbolFile& symbolFile);
	~RelevantSymbols ();

	RelevantSymbols (const RelevantSymbols&)					= delete;
	RelevantSymbols&	operator=	(const RelevantSymbols&)	= delete;

	void				Enumerate	(const SymbolProcessor& process) const;

private:
	std::vector<SymbolPtr>		symbols;
//	std::vector<std::string>	names;
};

}
}


#endif