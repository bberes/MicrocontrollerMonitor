#include "Request.hpp"


Communication::Request::Request (UInt8 processorID)
	: processorID (processorID)
{
}


Communication::Request::~Request () = default;