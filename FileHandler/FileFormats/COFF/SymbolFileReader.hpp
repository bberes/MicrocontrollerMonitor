#pragma once
#ifndef FileHandler__COFF_SymbolFileReader__hpp
#define FileHandler__COFF_SymbolFileReader__hpp

// #ExportHeader
#include "FileHandlerExport.hpp"

// #Standard
#include <memory>

// #FileHandler
#include "FileHandlerTypes.hpp"


namespace File::COFF {

FILEHANDLER_EXPORT
std::shared_ptr<SymbolFile> ReadSymbolFile (const QString& fileName);

}


#endif