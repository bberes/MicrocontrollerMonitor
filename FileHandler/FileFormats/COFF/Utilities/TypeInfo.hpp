#pragma once
#ifndef FileHandler__COFF_TypeInfo__hpp
#define FileHandler__COFF_TypeInfo__hpp

// #FileHandler
#include "FileHandlerTypes.hpp"


namespace File::COFF {

// #TODO Rethink this class and its role!
// Idea: class ObjectStore should be created like class MessageStore
class TypeInfo final {
public:
	explicit TypeInfo (const Object& object, const TypeDescriptor& typeDescriptor);

	static Object* Create (const TypeDescriptor& typeDescriptor, const SymbolEntry& symbol);
};

}


#endif