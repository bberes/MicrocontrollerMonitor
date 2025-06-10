#pragma once
#ifndef FileHandler__COFF_SymbolTableEntry__hpp
#define FileHandler__COFF_SymbolTableEntry__hpp

// #Standard
#include <memory>
#include <string>

// #FileHandler
#include "FileFormats\COFF\Types\EntryTypes.hpp"
#include "FileHandlerTypes.hpp"
#include "StorageClass.hpp"
#include "TableEntry.hpp"
#include "TypeDescriptor.hpp"


namespace File {
namespace COFF {

class SymbolTableEntry final : public TableEntry {
public:
	explicit SymbolTableEntry (DeserializationSelector);
	virtual ~SymbolTableEntry ();

	inline	bool				HasAuxiliaryEntry	() const;
	inline	AuxiliaryConstPtr	GetAuxiliaryEntry	() const;
	inline	void				SetAuxiliaryEntry	(const AuxiliaryConstPtr& auxiliaryEntry);

			std::string			GetName				(const SymbolFile& symbolFile) const;
	inline	UInt32				GetValue			() const;
	inline	TypeDescriptor		GetTypeSpecifier	() const;
	inline	StorageClass		GetStorageClass		() const;

	virtual EntryType			GetType				() const override;

	virtual size_t				Read				(DataStream& is) override;
	virtual size_t				Write				(DataStream& os) const override;

private:
	UInt8				symbolName[8];
	UInt32				symbolValue;
	UInt16				sectionNumber;
	UInt16				reserved;
	StorageClass		storageClass;
	UInt8				numOfAuxiliaryEntries;	// it can be 0 or 1

	AuxiliaryConstPtr	auxiliaryEntry;
};

}
}


inline bool File::COFF::SymbolTableEntry::HasAuxiliaryEntry () const
{
	return auxiliaryEntry != nullptr;
}

inline File::COFF::AuxiliaryConstPtr File::COFF::SymbolTableEntry::GetAuxiliaryEntry () const
{
	return auxiliaryEntry;
}

inline void File::COFF::SymbolTableEntry::SetAuxiliaryEntry (const AuxiliaryConstPtr& auxiliaryEntry)
{
	this->auxiliaryEntry = auxiliaryEntry;
}

inline UInt32 File::COFF::SymbolTableEntry::GetValue () const
{
	return symbolValue;
}

inline File::COFF::TypeDescriptor File::COFF::SymbolTableEntry::GetTypeSpecifier () const
{
	return TypeDescriptor (reserved);
}

inline StorageClass File::COFF::SymbolTableEntry::GetStorageClass () const
{
	return storageClass;
}


#endif