#pragma once
#ifndef Communication__HiTerm_ProcessorID__hpp
#define Communication__HiTerm_ProcessorID__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "Serialization\Deserializable.hpp"
#include "Serialization\Serializable.hpp"

// #Communication
#include "DeviceRole.hpp"


namespace Communication::HiTerm {

class COMMUNICATION_EXPORT ProcessorID final
	: private Serializable
	, private Deserializable
{
public:
	explicit ProcessorID (DeserializationSelector);
	explicit ProcessorID (UInt8 id, DeviceRole role);

	inline UInt8		GetID	() const { return id;   }
	inline DeviceRole	GetRole	() const { return role; }

	virtual size_t		Read	(DataStream& is) override;
	virtual size_t		Write	(DataStream& os) const override;

private:
	UInt8		id;
	DeviceRole	role;
};

}


#endif