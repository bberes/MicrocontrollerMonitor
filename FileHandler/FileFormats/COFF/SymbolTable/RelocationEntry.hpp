#pragma once
#ifndef FileHandler__COFF_RelocationEntry__hpp
#define FileHandler__COFF_RelocationEntry__hpp

// #Kernel
#include "Serialization\Deserializable.hpp"
#include "Serialization\Serializable.hpp"
#include "Types\BaseTypes.hpp"


namespace File {
namespace COFF {

class RelocationEntry final
	: private Serializable
	, private Deserializable
{
public:
	explicit RelocationEntry (DeserializationSelector);

	virtual size_t	Read	(DataStream& is) override;
	virtual size_t	Write	(DataStream& os) const override;

private:
	UInt32	virtualAddress;
	UInt16	symbolTableIndex;
//	UInt16	reserved;
	UInt16	relocationType;
};

}
}


#endif