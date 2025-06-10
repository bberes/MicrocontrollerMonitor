#include "ReadVariablesRequest.hpp"


Communication::ReadVariablesRequest::ReadVariablesRequest (UInt8 processorID, const MemoryRefs& memoryRefs)
	: Request		(processorID)
	, memoryRefs	(memoryRefs)
{
}