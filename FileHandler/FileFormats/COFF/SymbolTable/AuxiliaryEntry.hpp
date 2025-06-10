#pragma once
#ifndef FileHandler__COFF_AuxiliaryEntry__hpp
#define FileHandler__COFF_AuxiliaryEntry__hpp

// #Kernel
#include "Types\BaseTypes.hpp"

// #FileHandler
#include "TableEntry.hpp"


namespace File {
namespace COFF {

class AuxiliaryEntry final : public TableEntry {
public:
	explicit AuxiliaryEntry (DeserializationSelector);

	// #ToDo: Remove these functions. There should be an interpreter entity (like an extension or so).
	void				DecreaseDimension			();
	bool				IsMultidimensional			() const;
	UInt16				GetArrayDimensionSize		(size_t dimIndex = 0u) const;

	inline UInt32		GetSectionLength			() const;
	inline UInt16		GetNumOfRelocationEntries	() const;
	inline UInt16		GetNumOfLineNumberEntries	() const;

	virtual EntryType	GetType						() const override;

	virtual size_t		Read						(DataStream& is) override;
	virtual size_t		Write						(DataStream& os) const override;

private:
	UInt32	sectionLength;
	UInt16	numOfRelocationEntries;
	UInt16	numOfLineNumberEntries;
	UInt8	notUsed[10]; // zero filled
};

}
}


inline UInt32 File::COFF::AuxiliaryEntry::GetSectionLength () const
{
	return sectionLength;
}

inline UInt16 File::COFF::AuxiliaryEntry::GetNumOfRelocationEntries () const
{
	return numOfRelocationEntries;
}

inline UInt16 File::COFF::AuxiliaryEntry::GetNumOfLineNumberEntries () const
{
	return numOfLineNumberEntries;
}


#endif