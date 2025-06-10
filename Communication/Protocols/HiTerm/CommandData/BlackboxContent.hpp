#pragma once
#ifndef Communication__HiTerm_BlackboxContent__hpp
#define Communication__HiTerm_BlackboxContent__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Standard
#include <vector>

// #Kernel
#include "Serialization\Deserializable.hpp"
#include "Serialization\Serializable.hpp"
#include "Types\BaseTypes.hpp"


namespace Communication::HiTerm {

class COMMUNICATION_EXPORT BlackboxContent final
	: private Serializable
	, private Deserializable
{
public:
	using Content = std::vector<UInt32>;

	class COMMUNICATION_EXPORT Info final
		: private Serializable
		, private Deserializable
	{
	public:
		explicit Info (DeserializationSelector);
		explicit Info (UInt32 address, UInt16 length);

		virtual size_t	Read		(DataStream& is) override;
		virtual size_t	Write		(DataStream& os) const override;

		inline UInt32	GetAddress	() const { return address; }
		inline UInt16	GetLength	() const { return length;  }

		static constexpr
		size_t	GetSize		() { return sizeof (address) + sizeof (length); }

		static constexpr
		size_t	MaxLength	() { return std::numeric_limits<decltype (length)>::max (); }

	private:
		UInt32	address;
		UInt16	length;
	};

	explicit BlackboxContent (DeserializationSelector);
	explicit BlackboxContent (UInt32 address, const Content& content);

	virtual size_t	Read		(DataStream& is) override;
	virtual size_t	Write		(DataStream& os) const override;

	const Info&		GetInfo		() const { return info;    }
	const Content&	GetContent	() const { return content; }
	size_t			GetSize		() const;

private:
	Info	info;
	Content	content;
};

}


#endif