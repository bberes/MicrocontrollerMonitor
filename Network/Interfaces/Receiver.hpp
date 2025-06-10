#pragma once
#ifndef Network__Receiver__hpp
#define Network__Receiver__hpp

// #ExportHeader
#include "NetworkExport.hpp"

// #Kernel
#include "KernelTypes.hpp"


namespace Network {

class NETWORK_EXPORT Receiver {
public:
	virtual ~Receiver ();

	virtual void Receive (const ByteArray& byteArray) = 0;
};

}


#endif