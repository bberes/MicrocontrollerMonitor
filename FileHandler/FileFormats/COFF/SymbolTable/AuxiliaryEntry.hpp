#pragma once
#ifndef FileHandler__COFF_AuxiliaryEntry__hpp
#define FileHandler__COFF_AuxiliaryEntry__hpp

// #Kernel
#include "Types\BaseTypes.hpp"

// #FileHandler
#include "TableEntry.hpp"


namespace File::COFF {

class AuxEntry final : public TableEntry {
public:
	explicit AuxEntry (DeserializationSelector);

	// #ToDo: Remove these functions. There should be an interpreter entity (like an extension or so).
	void				DecreaseDimension			();
	bool				IsMultidimensional			() const;
	UInt16				GetArrayDimensionSize		(size_t dimIndex = 0u) const;

	inline UInt32		GetSectionLength			() const { return sectionLength; }
	inline UInt16		GetNumOfRelocationEntries	() const { return numOfRelocationEntries; }
	inline UInt16		GetNumOfLineNumberEntries	() const { return numOfLineNumberEntries; }

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


#endif