#pragma once
#ifndef Communication__HiTerm_BlackboxContent_DEPRECATED__hpp
#define Communication__HiTerm_BlackboxContent_DEPRECATED__hpp

// #Communication
#include "BlackboxContent.hpp"


namespace Communication::HiTerm::Preferred {

using Info		= ::Communication::HiTerm::BlackboxContent::Info;
using Content	= ::Communication::HiTerm::BlackboxContent::Content;

}


namespace Communication::HiTerm::Deprecated {

class COMMUNICATION_EXPORT BlackboxContent final
	: private Serializable
	, private Deserializable
{
public:
	explicit BlackboxContent (DeserializationSelector);
	explicit BlackboxContent (const Preferred::Info& info, const Preferred::Content& content);

	virtual size_t				Read		(DataStream& is) override;
	virtual size_t				Write		(DataStream& os) const override;

	const Preferred::Info&		GetInfo		() const { return info;    }
	const Preferred::Content&	GetContent	() const { return content; }
	size_t						GetSize		() const;

private:
	Preferred::Info		info;
	Preferred::Content	content;
};

}


#endif