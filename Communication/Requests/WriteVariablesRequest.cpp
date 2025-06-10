#include "WriteVariablesRequest.hpp"


Communication::WriteVariablesRequest::WriteVariablesRequest (UInt8 processorID, const Variables& variables)
	: Request		(processorID)
	, variables		(variables)
{
}