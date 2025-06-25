#pragma once
#ifndef FileHandler__COFF_SymbolTree__hpp
#define FileHandler__COFF_SymbolTree__hpp

// #ExportHeader
#include "FileHandlerExport.hpp"

// #Kernel
#include "Types\Vector.hpp"

// #FileHandler
#include "FileHandlerTypes.hpp"


namespace File::COFF {

class FILEHANDLER_EXPORT SymbolTree final {
public:
	explicit SymbolTree (const SymbolFile& symbolFile);
	~SymbolTree ();

	void	EnumerateLeaves	(const ObjectProcessor& process) const;

private:
	void	Build			(const SymbolFile& symbolFile);

private:
	Vector<Object*> objects;
};

}


#endif