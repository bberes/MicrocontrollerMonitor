#include "TabRequest.hpp"


Communication::TabRequest::TabRequest (UInt8 processorID, UInt8 tabIndex)
	: Request	(processorID)
	, tabIndex	(tabIndex)
{
}