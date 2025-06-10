#pragma once
#ifndef FileHandler__COFF_FileHeader__hpp
#define FileHandler__COFF_FileHeader__hpp

// #Kernel
#include "Serialization\Deserializable.hpp"
#include "Serialization\Serializable.hpp"

// #FileHandler
#include "HeaderFlags.hpp"
#include "TargetID.hpp"


namespace File {
namespace COFF {

class FileHeader final
	: private Serializable
	, private Deserializable
{
public:
	explicit FileHeader (DeserializationSelector);

	virtual size_t	Read							(DataStream& is) override;
	virtual size_t	Write							(DataStream& os) const override;

//	UInt16			GetVersion						() const;
	UInt16			GetNumOfSectionHeaders			() const;
//	Int32			GetTimeAndDateStamp				() const;
	Int32			GetStartAddressOfSymbolTable	() const;
	Int32			GetNumOfEntriesInSymbolTable	() const;
	UInt16			GetSizeOfTheOptionalHeader		() const;
//	HeaderFlags		GetFlags						() const;
	TargetID		GetTargetID						() const;

private:
	UInt16		versionID;
	UInt16		numOfSectinoHeaders;
	Int32		timeAndDateStamp;
	Int32		startAddressOfSymbolTable;
	Int32		numOfEntriesInSymbolTable;
	UInt16		sizeOfTheOptionalHeader;	// it can be 0 or 28
	HeaderFlags	flags;
	UInt16		targetID;
};

}
}


#endif