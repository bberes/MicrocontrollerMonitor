#pragma once
#ifndef Communication__PingRequest__hpp
#define Communication__PingRequest__hpp

// #Communication
#include "Request.hpp"


namespace Communication {

class COMMUNICATION_EXPORT PingRequest final : public Request {
public:
	DECLARE_CLASS_NAME (Communication, PingRequest)

	explicit PingRequest (UInt8 processorID);
};

}


#endif