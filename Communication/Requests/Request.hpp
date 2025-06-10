#pragma once
#ifndef Communication__Request__hpp
#define Communication__Request__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "Types\BaseTypes.hpp"
#include "Types\NamedType.hpp"


namespace Communication {

class COMMUNICATION_EXPORT Request : private NamedType {
public:
	explicit Request (UInt8 processorID);
	virtual ~Request ();

	inline UInt8		GetProcessorID	() const { return processorID; }
	virtual const char*	ClassName		() const override = 0;

private:
	UInt8 processorID;
};

}


#endif