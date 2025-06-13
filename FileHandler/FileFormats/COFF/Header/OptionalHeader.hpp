#pragma once
#ifndef FileHandler__COFF_OptionalHeader__hpp
#define FileHandler__COFF_OptionalHeader__hpp

// #Kernel
#include "Serialization\Deserializable.hpp"
#include "Serialization\Serializable.hpp"
#include "Types\BaseTypes.hpp"


namespace File::COFF {

class OptionalHeader final
	: private Serializable
	, private Deserializable
{
public:
	explicit OptionalHeader (DeserializationSelector);

	virtual size_t	Read	(DataStream& is) override;
	virtual size_t	Write	(DataStream& os) const override;

private:
	Int16	optionalFileHeaderNum;	// it must be 0x0108
	Int16	versionStamp;
	Int32	sizeOfExecutableCode;
	Int32	sizeOfInitializedData;
	Int32	sizeOfUninitializedData;
	Int32	entryPoint;
	Int32	startAddressOfExecutableData;
	Int32	startAddressOfInitializedData;
};

}


#endif