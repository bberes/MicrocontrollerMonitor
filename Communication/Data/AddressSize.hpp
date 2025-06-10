#pragma once
#ifndef Communication__AddressSize__hpp
#define Communication__AddressSize__hpp

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication {

enum class AddressSize : UInt8 {
	Size1Byte  = 1u,
	Size2Bytes = 2u,
	Size4Bytes = 4u,
	Size8Bytes = 8u
};

}


#endif