#pragma once
#ifndef FileHandler__COFF_SymbolEntry__hpp
#define FileHandler__COFF_SymbolEntry__hpp

// #Standard
#include <string>

// #Kernel
#include "Types\Owner.hpp"

// #FileHandler
#include "FileHandlerTypes.hpp"
#include "StorageClass.hpp"
#include "TableEntry.hpp"
#include "TypeDescriptor.hpp"


namespace File::COFF {

class SymbolEntry final : public TableEntry {
public:
	SymbolEntry (const SymbolEntry&);
	explicit SymbolEntry (DeserializationSelector);
	virtual ~SymbolEntry () override;

	inline	bool				HasAuxiliaryEntry	() const { return auxiliaryEntry != nullptr; }
			const AuxEntry&		GetAuxiliaryEntry	() const;
			void				SetAuxiliaryEntry	(Owner<AuxEntry> auxEntry);

			std::string			GetName				(const SymbolFile& symbolFile) const;
	inline	UInt32				GetValue			() const { return symbolValue; }
	inline	TypeDescriptor		GetTypeSpecifier	() const { return TypeDescriptor (reserved); }
	inline	StorageClass		GetStorageClass		() const { return storageClass; }

	virtual EntryType			GetType				() const override;

	virtual size_t				Read				(DataStream& is) override;
	virtual size_t				Write				(DataStream& os) const override;

private:
	UInt8			symbolName[8];
	UInt32			symbolValue;
	UInt16			sectionNumber;
	UInt16			reserved;
	StorageClass	storageClass;
	UInt8			numOfAuxiliaryEntries;	// it can be 0 or 1

	Owner<AuxEntry>	auxiliaryEntry;
};

}


#endif