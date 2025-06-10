#pragma once
#ifndef Communication__TabValuesRequest__hpp
#define Communication__TabValuesRequest__hpp

// #Communication
#include "TabRequest.hpp"


namespace Communication {

class COMMUNICATION_EXPORT TabValuesRequest final : public TabRequest {
public:
	DECLARE_CLASS_NAME (Communication, TabValuesRequest)

	explicit TabValuesRequest (UInt8 processorID, UInt8 tabIndex);
};

}


#endif