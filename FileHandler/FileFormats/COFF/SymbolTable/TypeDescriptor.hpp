#pragma once
#ifndef FileHandler__COFF_TypeDescriptor__hpp
#define FileHandler__COFF_TypeDescriptor__hpp

// #ExportHeader
#include "FileHandlerExport.hpp"

// #Standard
#include <string>

// #Kernel
#include "Types\BaseTypes.hpp"


namespace File::COFF {

enum class BaseType : UInt8 {
	Void,
	UNKNOWN,
	Char,
	Int16,
	Int16_Other,
	Int32,
	Float,
	Double,
	Struct,
	Union,
	Enum,
	MemberOfEnum,
	UChar,
	UInt16,
	UInt16_Other,
	UInt32
};


enum class DerivedType : UInt8 {
	None,
	Pointer,
	Function,
	Array
};


class FILEHANDLER_EXPORT TypeDescriptor final {
public:
	explicit TypeDescriptor (
		const BaseType		baseType,
		const DerivedType	firstDerived	= DerivedType::None,
		const DerivedType	secondDerived	= DerivedType::None
	);
	explicit TypeDescriptor (const UInt16 typeSpecifier);

	BaseType		GetBaseType			() const;
	DerivedType		GetFirstDerived		() const;
	DerivedType		GetSecondDerived	() const;

	operator UInt16						() const;

private:
	const UInt16	typeSpecifier;
};


std::string ToString (BaseType baseType);

// #ToDo: move these into the cpp (or remove), use enum BaseType instead
constexpr char TextVoid[]	= "VOID";
constexpr char TextChar[]	= "CHAR";
constexpr char TextInt16[]	= "S16";
constexpr char TextInt32[]	= "S32";
constexpr char TextFloat[]	= "FLOAT";
constexpr char TextStruct[]	= "STRUCT";
constexpr char TextEnum[]	= "ENUM";
constexpr char TextUChar[]	= "UCHAR";
constexpr char TextUInt16[]	= "U16";
constexpr char TextUInt32[]	= "U32";

}


#endif