#pragma once
#ifndef Communication__HiTerm_DeviceRole__hpp
#define Communication__HiTerm_DeviceRole__hpp

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication::HiTerm {

enum class DeviceRole : UInt16 {
	Master = 0x5A00,
	Slave  = 0xA500
};

}


#endif