#pragma once
#ifndef Communication__MemoryReference__hpp
#define Communication__MemoryReference__hpp

// #Standard
#include <vector>

// #Communication
#include "AddressSize.hpp"
#include "CommunicationTypes.hpp"
#include "VariableSize.hpp"


namespace Communication {

class MemoryReference final {
public:
	template <typename AddressType>
	explicit MemoryReference (AddressType address, VariableSize variableSize);

	bool			operator!=			(const MemoryReference& other) const;

	template <typename AddressType>
	AddressType		GetAddress			() const;

	AddressSize		GetAddressSize		() const { return addressSize;  }
	VariableSize	GetVariableSize		() const { return variableSize; }

private:
	void			CheckAddressSize	(size_t size) const;

private:
	UInt64			address;
	AddressSize		addressSize;
	VariableSize	variableSize;
};

}


template <typename AddrType>
constexpr bool is_allowed_addr_type_v =
	std::is_same_v<AddrType, UInt8>  ||
	std::is_same_v<AddrType, UInt16> ||
	std::is_same_v<AddrType, UInt32> ||
	std::is_same_v<AddrType, UInt64>
	;


template <typename AddressType>
inline Communication::MemoryReference::MemoryReference (AddressType address, VariableSize variableSize)
	: address		(address)
	, addressSize	(static_cast<AddressSize> (sizeof (AddressType)))
	, variableSize	(variableSize)
{
	static_assert (is_allowed_addr_type_v<AddressType>, "Type must be one of these: UInt8, UInt16, UInt32 or UInt64!");
}


inline bool Communication::MemoryReference::operator!= (const MemoryReference& other) const
{
	return
		address      != other.address      ||
		addressSize  != other.addressSize  ||
		variableSize != other.variableSize
		;
}


template <typename AddressType>
inline AddressType Communication::MemoryReference::GetAddress () const
{
	static_assert (is_allowed_addr_type_v<AddressType>, "Type must be one of these: UInt8, UInt16, UInt32 or UInt64!");
	CheckAddressSize (sizeof (AddressType));
	return static_cast<AddressType> (address);
}


#endif