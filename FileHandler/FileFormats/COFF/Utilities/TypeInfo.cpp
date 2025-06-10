#include "TypeInfo.hpp"

// #Standard
#include <unordered_map>

// #Kernel
#include "Utilities\Debug.hpp"

// #FileHandler
#include "FileFormats\COFF\SymbolTable\TypeDescriptor.hpp"
#include "FileFormats\COFF\Types\ObjectPtr.hpp"
#include "TreeNodes.hpp"


namespace File {
namespace COFF {

namespace {

std::unordered_map<UInt16, ObjectConstPtr>& GetTypeInformations ()
{
	static std::unordered_map<UInt16, ObjectConstPtr> map;
	return map;
}

}


TypeInfo::TypeInfo (const Object& object, const TypeDescriptor& typeDescriptor)
{
	auto& map = GetTypeInformations ();
	ASSERT (map.count (typeDescriptor) == 0u);

	map.insert (std::pair<UInt16, ObjectConstPtr> (typeDescriptor, object.Create (nullptr)));
}


Object* TypeInfo::Create (const TypeDescriptor& typeDescriptor, const SymbolConstPtr& symbol)
{
	UInt16 key = typeDescriptor;
	INSPECT ((key & 0xFFF0) == 0u); // Current limitation. May change later.
	key &= 0x000F;

	auto& map = GetTypeInformations ();
	ASSERT (map.count (key) > 0u);

	return map[key]->Create (symbol);
}

}
}