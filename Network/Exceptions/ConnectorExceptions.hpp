#pragma once
#ifndef Network__ConnectorExceptions__hpp
#define Network__ConnectorExceptions__hpp

// #Standard
#include <stdexcept>


namespace Network {

class TransmitError : public std::runtime_error {
public:
	using runtime_error::runtime_error;
};

}


#endif