#pragma once
#ifndef Communication__VariableSize__hpp
#define Communication__VariableSize__hpp

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication {

enum class VariableSize : UInt8 {
	Size1Byte  = 1u,
	Size2Bytes = 2u,
	Size4Bytes = 4u,
	Size8Bytes = 8u
};

}


#endif