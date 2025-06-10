#pragma once
#ifndef Communication__TabDataRequest__hpp
#define Communication__TabDataRequest__hpp

// #Communication
#include "TabRequest.hpp"


namespace Communication {

class COMMUNICATION_EXPORT TabDataRequest final : public TabRequest {
public:
	DECLARE_CLASS_NAME (Communication, TabDataRequest)

	explicit TabDataRequest (UInt8 processorID, UInt8 tabIndex);
};

}


#endif