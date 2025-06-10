#include "ReadArrayRequest.hpp"


Communication::ReadArrayRequest::ReadArrayRequest (UInt8 processorID, UInt32 address, UInt16 length)
	: Request	(processorID)
	, address	(address)
	, length	(length)
{
}