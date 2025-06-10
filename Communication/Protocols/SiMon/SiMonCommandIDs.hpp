#pragma once
#ifndef Communication__SiMon_CommandIDs__hpp
#define Communication__SiMon_CommandIDs__hpp

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication::SiMon::CommandID {

	constexpr UInt8 ReadVariable	= 0x10;
	constexpr UInt8 WriteVariable	= 0x11;
	constexpr UInt8 ReadBBXData		= 0x12;

	constexpr UInt8 Reboot			= 0x20;
	constexpr UInt8 ClearSector		= 0x21;
	constexpr UInt8 ProgramAPI		= 0x22;
	constexpr UInt8 ProgramBOOT		= 0x23;
	constexpr UInt8 ProgramApp		= 0x24;

	constexpr UInt8 Ping			= 0x30;

}


#endif