#include "TypeDescriptor.hpp"

// #Kernel
#include "Utilities\Debug.hpp"


namespace {

using File::COFF::BaseType;
using File::COFF::DerivedType;


UInt16 GetTypeSpecifier (const BaseType baseType, const DerivedType firstDerived, const DerivedType secondDerived)
{
	const UInt16 base	= (static_cast<UInt16> (baseType)		& 0x0Fu);
	const UInt16 first	= (static_cast<UInt16> (firstDerived)	& 0x03u);
	const UInt16 second	= (static_cast<UInt16> (secondDerived)	& 0x03u);

	return (base | (first << 4) | (second << 6));
}

}


File::COFF::TypeDescriptor::TypeDescriptor (const BaseType baseType, const DerivedType firstDerived, const DerivedType secondDerived)
	: typeSpecifier	(GetTypeSpecifier (baseType, firstDerived, secondDerived))
{
}


File::COFF::TypeDescriptor::TypeDescriptor (const UInt16 typeSpecifier)
	: typeSpecifier	(typeSpecifier)
{
	ASSERT ((typeSpecifier >> 8) == 0u);
}


File::COFF::BaseType File::COFF::TypeDescriptor::GetBaseType () const
{
	return static_cast<BaseType> (typeSpecifier & 0x0Fu);
}


File::COFF::DerivedType File::COFF::TypeDescriptor::GetFirstDerived () const
{
	return static_cast<DerivedType> ((typeSpecifier >> 4) & 0x03u);
}


File::COFF::DerivedType File::COFF::TypeDescriptor::GetSecondDerived () const
{
	return static_cast<DerivedType> ((typeSpecifier >> 6) & 0x03u);
}


File::COFF::TypeDescriptor::operator UInt16 () const
{
	return typeSpecifier;
}


std::string File::COFF::ToString (BaseType baseType)
{
	switch (baseType) {
	case BaseType::Void:			return TextVoid;
	case BaseType::UNKNOWN:			return "";
	case BaseType::Char:			return TextChar;
	case BaseType::Int16:			return "";
	case BaseType::Int16_Other:		return TextInt16;
	case BaseType::Int32:			return TextInt32;
	case BaseType::Float:			return TextFloat;
	case BaseType::Double:			return "";
	case BaseType::Struct:			return TextStruct;
	case BaseType::Union:			return "";
	case BaseType::Enum:			return TextEnum;
	case BaseType::MemberOfEnum:	return "";
	case BaseType::UChar:			return TextUChar;
	case BaseType::UInt16:			return "";
	case BaseType::UInt16_Other:	return TextUInt16;
	case BaseType::UInt32:			return TextUInt32;
	}
	ASSERT (false, "The baseType variable has illegal value.");
	return std::string ();
}