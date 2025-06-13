#pragma once
#ifndef FileHandler__FileHandlerTypes__hpp
#define FileHandler__FileHandlerTypes__hpp

// #Standard
#include <functional>


class QString;


namespace File::COFF {
	class AuxEntry;
	class SymbolEntry;

	class Object;
	class OptionalHeader;
	class SectionHeaderCOFF2;
	class SymbolFile;
	class TypeDescriptor;

	using ObjectProcessor = std::function<void (const Object&)>;
}


#endif