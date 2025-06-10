#pragma once
#ifndef Communication__ReadArrayRequest__hpp
#define Communication__ReadArrayRequest__hpp

// #Communication
#include "Request.hpp"


namespace Communication {

class COMMUNICATION_EXPORT ReadArrayRequest final : public Request {
public:
	DECLARE_CLASS_NAME (Communication, ReadArrayRequest)

	explicit ReadArrayRequest (UInt8 processorID, UInt32 address, UInt16 length);

	UInt32	GetAddress	() const { return address; }
	UInt16	GetLength	() const { return length;  }

private:
	// #ToDo: address and length info needed in general form
	UInt32	address;
	UInt16	length;
};

}


#endif