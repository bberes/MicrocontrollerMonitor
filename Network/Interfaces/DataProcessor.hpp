#pragma once
#ifndef Network__DataProcessor__hpp
#define Network__DataProcessor__hpp

// #ExportHeader
#include "NetworkExport.hpp"

// #Kernel
#include "KernelTypes.hpp"


namespace Network {

class NETWORK_EXPORT DataProcessor {
public:
	virtual ~DataProcessor ();

	virtual void Process (ByteArray& byteArray) = 0;
};

}


#endif