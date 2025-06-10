#pragma once
#ifndef Communication__HiTerm_MonTab__hpp
#define Communication__HiTerm_MonTab__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Standard
#include <string>
#include <vector>

// #Kernel
#include "Serialization\Deserializable.hpp"
#include "Serialization\Serializable.hpp"
#include "Types\BaseTypes.hpp"

// #Communication
#include "MonTabType.hpp"
#include "MonTabUnit.hpp"


namespace Communication::HiTerm {

class MonTab final {
public:
	class Entry;
	using Entries = std::vector<Entry>;

public:
	class Entry final
		: private Serializable
		, private Deserializable
	{
	public:
		using Name	= std::string;
		using Unit	= MonTabUnit;
		using Type	= MonTabType;
		using Ptr	= UInt32;
		using PMax	= UInt32;
		using PMin	= UInt32;

		explicit Entry (DeserializationSelector);
		explicit Entry (Name, Unit, Type, Ptr, PMax, PMin);

		virtual size_t	Read	(DataStream& is) override;
		virtual size_t	Write	(DataStream& os) const override;

		inline Name		GetName	() const { return name; }
		inline Unit		GetUnit	() const { return unit; }
		inline Type		GetType	() const { return type; }
		inline Ptr		GetPtr	() const { return ptr;  }
		inline PMax		GetPMax	() const { return pMax; }
		inline PMin		GetPMin	() const { return pMin; }

		inline static constexpr size_t GetSize ();

	public:
		static constexpr UInt16 NameFieldLength = 12u;

	private:
		Name	name;
		Unit	unit;
		Type	type;
		Ptr		ptr;
		PMax	pMax;
		PMin	pMin;
	};

public:
	UInt16			GetLength	() const;
	size_t			ReadData	(DataStream& ds, UInt16 length);
	size_t			WriteData	(DataStream& ds) const;

	const Entries&	GetEntries	() const { return entries; }

private:
	Entries entries;
};

}


inline constexpr size_t Communication::HiTerm::MonTab::Entry::GetSize ()
{
	return sizeof (UInt16) * NameFieldLength + sizeof (Unit) + sizeof (Type) + sizeof (Ptr) + sizeof (PMax) + sizeof (PMin);
}


#endif