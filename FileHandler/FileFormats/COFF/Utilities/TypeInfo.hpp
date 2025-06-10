#pragma once
#ifndef FileHandler__COFF_TypeInfo__hpp
#define FileHandler__COFF_TypeInfo__hpp

// #FileHandler
#include "FileFormats\COFF\Types\EntryTypes.hpp"
#include "FileHandlerTypes.hpp"


namespace File {
namespace COFF {

// #TODO Rethink this class and its role!
// Idea: class ObjectStore should be created like class MessageStore
class TypeInfo final {
public:
	explicit TypeInfo (const Object& object, const TypeDescriptor& typeDescriptor);

	static Object* Create (const TypeDescriptor& typeDescriptor, const SymbolConstPtr& symbol);
};

}
}


#endif