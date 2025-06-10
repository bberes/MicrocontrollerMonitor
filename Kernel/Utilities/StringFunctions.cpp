#include "StringFunctions.hpp"


std::string Utilities::BytesToString (const UInt8* const bytes, const UInt32 size/* = UInt32MAX*/)
{
	std::string name;
	for (UInt32 i = 0u; i < size && bytes[i] != '\0'; ++i) {
		name += bytes[i];
	}
	return name;
}