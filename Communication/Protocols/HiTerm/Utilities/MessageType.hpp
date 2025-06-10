#pragma once
#ifndef Communication__HiTerm_MessageType__hpp
#define Communication__HiTerm_MessageType__hpp

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication::HiTerm {

enum class MessageType : UInt8 {
	Command		= 0x00,
	Response	= 0x80
};

}


#endif