#pragma once
#ifndef Communication__HiTermExceptions__hpp
#define Communication__HiTermExceptions__hpp

// #Standard
#include <stdexcept>

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication::HiTerm {

class MismatchingCRC : public std::runtime_error {
public:
	using runtime_error::runtime_error;
};


class InvalidTypeID : public std::invalid_argument {
public:
	explicit InvalidTypeID (UInt16 typeID, const std::string& message)
		: invalid_argument	(message)
		, typeID			(typeID)
	{
	}

	UInt16 GetTypeID () const { return typeID; }

private:
	UInt16 typeID;
};


class MissingTypeID : public InvalidTypeID {
public:
	explicit MissingTypeID (UInt16 typeID, const std::string& message)
		: InvalidTypeID (typeID, message)
	{
	}
};

}


#endif