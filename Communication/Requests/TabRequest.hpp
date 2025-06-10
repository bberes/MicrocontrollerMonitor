#pragma once
#ifndef Communication__TabRequest__hpp
#define Communication__TabRequest__hpp

// #Communication
#include "Request.hpp"


namespace Communication {

class TabRequest : public Request {
public:
	explicit TabRequest (UInt8 processorID, UInt8 tabIndex);

	UInt8 GetTabIndex () const { return tabIndex; }

private:
	UInt8 tabIndex;
};

}


#endif