#pragma once
#ifndef FileHandler__COFF_SymbolFile__hpp
#define FileHandler__COFF_SymbolFile__hpp

// #ExportHeader
#include "FileHandlerExport.hpp"

// #Standard
#include <functional>
#include <vector>

// #Kernel
#include "Serialization\Deserializable.hpp"
#include "Serialization\Serializable.hpp"
#include "Types\ByteArray.hpp"
#include "Types\Owner.hpp"
#include "KernelTypes.hpp"

// #FileHandler
#include "Header\FileHeader.hpp"
#include "Types\EntryTypes.hpp"
#include "FileHandlerTypes.hpp"


class ISymbolFile
	: private Serializable
	, private Deserializable
{
public:
	constexpr explicit ISymbolFile (DeserializationSelector);
	virtual ~ISymbolFile ();

	virtual size_t	Read	(DataStream& is) override = 0;
	virtual size_t	Write	(DataStream& os) const override = 0;
};


namespace File {
namespace COFF {

class FILEHANDLER_EXPORT SymbolFile final : public ISymbolFile {
public:
//	SymbolFile ();
	explicit SymbolFile (DeserializationSelector, const ByteArray& byteArray);
	virtual ~SymbolFile () override;

	void				Enumerate		(const std::function<void (const SymbolEntry&)>& process) const;
	std::string			GetName			(const UInt32 index) const;
	SymbolConstPtr		GetEntryByIndex	(const UInt32 index) const;

	virtual size_t		Read			(DataStream& is) override;
	virtual size_t		Write			(DataStream& os) const override;

private:
//	SymbolFile ();
//	SymbolFile (const ByteArray& byteArray);
	SymbolFile (const SymbolFile&) = delete;
	SymbolFile&			operator=		(const SymbolFile&) = delete;

private:
	ByteArray							byteArray;

	FileHeader							header;
	Owner<OptionalHeader>				optionalHeader;
	std::vector<SectionHeaderCOFF2*>	sectionHeaders;
//	std::vector<>	;	//	Raw data for each initialized section
//	std::vector<>	;	//	Relocation information for each initialized section
	std::vector<SymbolEntry*>			symbols;
//	std::vector<>		strings;
};

}
}


constexpr ISymbolFile::ISymbolFile (DeserializationSelector ds)
	: Deserializable (ds)
{
}


#endif