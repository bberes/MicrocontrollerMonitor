#pragma once
#ifndef Communication__ReadVariablesRequest__hpp
#define Communication__ReadVariablesRequest__hpp

// #Standard
#include <vector>

// #Communication
#include "Data\MemoryReference.hpp"
#include "Request.hpp"


namespace Communication {

class COMMUNICATION_EXPORT ReadVariablesRequest final : public Request {
public:
	DECLARE_CLASS_NAME (Communication, ReadVariablesRequest)

	explicit ReadVariablesRequest (UInt8 processorID, const MemoryRefs& memoryRefs);

	const MemoryRefs& GetMemoryRefs () const { return memoryRefs; }

private:
	MemoryRefs memoryRefs;
};

}


#endif