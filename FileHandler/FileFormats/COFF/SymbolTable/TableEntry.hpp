#pragma once
#ifndef FileHandler__COFF_TableEntry__hpp
#define FileHandler__COFF_TableEntry__hpp

// #Kernel
#include "Serialization\Deserializable.hpp"
#include "Serialization\Serializable.hpp"


enum class EntryType {
	Symbol,
	Auxiliary
};


namespace File {
namespace COFF {

class TableEntry
	: private Serializable
	, private Deserializable
{
public:
	constexpr explicit TableEntry (RegularSelector);
	constexpr explicit TableEntry (DeserializationSelector);
	virtual ~TableEntry ();

	virtual EntryType		GetType	() const = 0;

	virtual size_t			Read	(DataStream& is) override = 0;
	virtual size_t			Write	(DataStream& os) const override = 0;

public:
	static constexpr size_t	Size	() { return 18u; }
};

}
}


constexpr File::COFF::TableEntry::TableEntry (RegularSelector rs)
	: Deserializable (rs)
{
}


constexpr File::COFF::TableEntry::TableEntry (DeserializationSelector ds)
	: Deserializable (ds)
{
}


#endif