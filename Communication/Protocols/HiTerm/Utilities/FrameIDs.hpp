#pragma once
#ifndef Communication__HiTerm_FrameIDs__hpp
#define Communication__HiTerm_FrameIDs__hpp

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication::HiTerm::FrameID {

	constexpr UInt8 STX		= 0x3C;
	constexpr UInt8 ETX		= 0x3E;
	constexpr UInt8 DLE		= 0x3D;
	constexpr UInt8 XDAT	= 0x30;

}


#endif