#pragma once
#ifndef FileHandler__COFF_SectionHeader__hpp
#define FileHandler__COFF_SectionHeader__hpp

// #Standard
#include <string>

// #Kernel
#include "Serialization\Deserializable.hpp"
#include "Serialization\Serializable.hpp"

// #FileHandler
#include "FileHandlerTypes.hpp"
#include "SectionFlags.hpp"
#include "TargetID.hpp"


namespace File::COFF {

class SectionHeaderBase
	: private Serializable
	, private Deserializable {
public:
	explicit SectionHeaderBase (DeserializationSelector);

	virtual size_t		Read							(DataStream& is) override final;
	virtual size_t		Write							(DataStream& os) const override final;

	virtual std::string	GetSectionName					(const SymbolFile& symbolFile) const = 0;
	virtual Int32		GetSizeInBytes					(const TargetID& targetID) const = 0;

	Int32				GetPhysicalAddress				() const;
	Int32				GetPointerToRawData				() const;

	Int32				GetPointerToRelocationEntries	() const;
	Int32				GetNumOfRelocationEntries		() const;

	UInt32				GetAlignment					(const TargetID& targetID) const;

private:
	virtual size_t		ReadImpl						(DataStream& is) = 0;
	virtual size_t		WriteImpl						(DataStream& os) const = 0;

protected:
	UInt8			sectionNameOrPointer[8];
private:
	Int32			physicalAddress;
	Int32			virtualAddress;
protected:
	Int32			sizeInBytesOrWords;
private:
	Int32			pointerToRawData;
	Int32			pointerToRelocationEntries;
	Int32			reserved_1;
protected:
	UInt32			numOfRelocationEntries;
	UInt32			numOfLineNumberEntries;
	SectionFlags	flags;
	UInt16			reserved_2;
	UInt16			memoryPageNumber;
};


class SectionHeaderCOFF1 final : public SectionHeaderBase {
public:
	explicit SectionHeaderCOFF1 (DeserializationSelector);

	virtual std::string	GetSectionName	(const SymbolFile& symbolFile) const override;
	virtual Int32		GetSizeInBytes	(const TargetID& targetID) const override;

private:
	virtual size_t		ReadImpl		(DataStream& is) override;
	virtual size_t		WriteImpl		(DataStream& os) const override;
};


class SectionHeaderCOFF2 final : public SectionHeaderBase {
public:
	explicit SectionHeaderCOFF2 (DeserializationSelector);

	virtual std::string	GetSectionName	(const SymbolFile& symbolFile) const override;
	virtual Int32		GetSizeInBytes	(const TargetID& targetID) const override;

private:
	virtual size_t		ReadImpl		(DataStream& is) override;
	virtual size_t		WriteImpl		(DataStream& os) const override;
};

}


#endif