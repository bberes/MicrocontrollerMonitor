#include "TypeInfo.hpp"

// #Kernel
#include "Types\HashTable.hpp"
#include "Types\Owner.hpp"
#include "Utilities\Debug.hpp"

// #FileHandler
#include "FileFormats\COFF\SymbolTable\TypeDescriptor.hpp"
#include "TreeNodes.hpp"


namespace File::COFF {

namespace {

HashTable<UInt16, Owner<const Object>>& GetTypeInformations ()
{
	static HashTable<UInt16, Owner<const Object>> map;
	return map;
}

}


TypeInfo::TypeInfo (const Object& object, const TypeDescriptor& typeDescriptor)
{
	auto& map = GetTypeInformations ();
	ASSERT (map.count (typeDescriptor) == 0u);

	map.insert (std::pair<UInt16, Owner<const Object>> (typeDescriptor, object.Create (SymbolEntry (ForDeserialization))));
}


Object* TypeInfo::Create (const TypeDescriptor& typeDescriptor, const SymbolEntry& symbol)
{
	UInt16 key = typeDescriptor;
	INSPECT ((key & 0xFFF0) == 0u); // Current limitation. May change later.
	key &= 0x000F;

	auto& map = GetTypeInformations ();
	ASSERT (map.count (key) > 0u);

	return map[key]->Create (symbol);
}

}