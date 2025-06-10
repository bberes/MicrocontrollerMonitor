#pragma once
#ifndef Communication__Variable__hpp
#define Communication__Variable__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Standard
#include <vector>

// #Kernel
#include "Types\BaseTypes.hpp"

// #Communication
#include "MemoryReference.hpp"


namespace Communication {

class COMMUNICATION_EXPORT Variable final {
public:
	template <typename ValueType, typename AddressType>
	inline explicit Variable (ValueType value, AddressType address);

	template <typename Type>
	inline Type			GetValue () const;

	inline MemoryRef	GetInfo  () const { return info; }

private:
	void CheckVariableSize (size_t size) const;

private:
	UInt64		value;
	MemoryRef	info;
};

}


template <typename ValueType, typename AddressType>
inline Communication::Variable::Variable (ValueType value, AddressType address)
	: value	(value)
	, info	(address, static_cast<VariableSize> (sizeof (ValueType)))
{
}


template <typename Type>
inline Type Communication::Variable::GetValue () const
{
	CheckVariableSize (sizeof (Type));
	Type returnValue {};
	std::memcpy (&returnValue, &value, sizeof (Type));
	return returnValue;
}


#endif