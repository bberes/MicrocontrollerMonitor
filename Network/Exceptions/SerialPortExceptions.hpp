#pragma once
#ifndef Network__SerialPortExceptions__hpp
#define Network__SerialPortExceptions__hpp

// #Standard
#include <stdexcept>

// #Kernel
#include "Types\BaseTypes.hpp"

// #Network
#include "Utilities\SerialPortErrorCode.hpp"


namespace Network::SerialPort {

class ConnectError : public std::runtime_error {
public:
	explicit ConnectError (ErrorCode errorCode, const std::string& message)
		: runtime_error	(message)
		, errorCode		(errorCode)
	{
	}

	ErrorCode GetErrorCode () const
	{
		return errorCode;
	}

private:
	ErrorCode errorCode;
};

}


#endif