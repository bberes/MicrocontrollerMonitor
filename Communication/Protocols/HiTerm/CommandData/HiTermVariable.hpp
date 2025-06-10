#pragma once
#ifndef Communication__HiTerm_Variable__hpp
#define Communication__HiTerm_Variable__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "Serialization\Deserializable.hpp"
#include "Serialization\Serializable.hpp"
#include "Types\BaseTypes.hpp"

// #Communication
#include "CommunicationTypes.hpp"


namespace Communication::HiTerm {

class Memory final
	: private Serializable
	, private Deserializable
{
public:
	enum Size : UInt8 {
		_1_Byte__ = 1u,
		_2_Bytes_ = 2u,
		_4_Bytes_ = 4u,
		_8_Bytes_ = 8u
	};

	explicit Memory (DeserializationSelector);
	explicit Memory (UInt32 address, Size memorySize);

	virtual size_t	Read		(DataStream& is) override;
	virtual size_t	Write		(DataStream& os) const override;

	UInt32			GetAddress	() const { return address; }
	Size			GetMemSize	() const;

	static constexpr size_t GetSize () { return sizeof (UInt32) + sizeof (Size); }

private:
	UInt32	address;
	Size	memorySize; // allocated bytes (NOT the size of addressing)
};

// #ToDo: rethink Variable classes
class Variable final
	: private Serializable
	, private Deserializable
{
public:
	explicit Variable (DeserializationSelector);
	explicit Variable (const Communication::Variable& variable);

	template <typename Type>
	explicit Variable (UInt32 address, Type value);

	virtual size_t	Read		(DataStream& is) override;
	virtual size_t	Write		(DataStream& os) const override;

	template <typename Type>
	Type			GetValue	() const;

	const Memory&	GetMemory	() const { return memory; }

	operator Communication::Variable () const;
	size_t			GetSize		() const;

private:
	void			CheckSize	(size_t size) const;

private:
	UInt64	value;
	Memory	memory;
};

}


template <typename Type>
Communication::HiTerm::Variable::Variable (UInt32 address, Type value)
	: Deserializable	(RegularConstructor)
	, value				(value)
	, memory			(address, static_cast<Memory::Size> (sizeof (Type)))
{
}


template <typename Type>
Type Communication::HiTerm::Variable::GetValue () const
{
	CheckSize (sizeof (Type));
	return static_cast<Type> (value);
}


#endif