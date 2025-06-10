#pragma once
#ifndef Communication__HiTerm_MonTabType__hpp
#define Communication__HiTerm_MonTabType__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Standard
#include <string>

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication::HiTerm {

enum MonTabType : UInt16 {
	Type_32bits		= 0x0000,
	Type_16bits		= 0x0001,
	Type_Signed		= Type_32bits,
	Type_Unsigned	= 0x0002,
	Type_IQn_Base	= 0x0004,	// Value of n can be 0 to 30. (Type_IQn = n * 0x0004)
	Type_HEX		= 0x0080,
	Type_Float		= 0x0100,
	Type_Writable	= 0x0200,
	Type_ShiftNBase = 0x0400,	// Value of N can be 0 to 16. (Type_ShiftN = n * 0x0400)

	Type_S32		= Type_Signed | Type_32bits,
	Type_S16		= Type_Signed | Type_16bits,
	Type_U32		= Type_Unsigned | Type_32bits,
	Type_U16		= Type_Unsigned | Type_16bits
};


namespace Mask {

constexpr UInt16 IQ		= 0x007C;
constexpr UInt16 Sign	= 0x0002;
constexpr UInt16 Shift	= 0x3C00;

}


constexpr UInt16 GetIQNumber (MonTabType type)
{
	return (type & Mask::IQ) >> 2;
}

constexpr bool IsUnsignedNumber (MonTabType type)
{
	return (type & Mask::Sign);
}

constexpr UInt16 GetShiftValue (MonTabType type)
{
	return (type & Mask::Shift) >> 10;
}


static_assert (sizeof (MonTabType) == 2u, "MonTabUnit must be 2-byte-length!");

}


#endif