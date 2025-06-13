#pragma once
#ifndef FileHandler__COFF_TargetID__hpp
#define FileHandler__COFF_TargetID__hpp

// #Kernel
#include "Types\BaseTypes.hpp"


namespace File::COFF {

enum class TargetID : UInt16 {
	TMS470			= 0x0097u,
	TMS320C5400		= 0x0098u,
	TMS320C6000		= 0x0099u,
	TMS320C5500		= 0x009Cu,
	TMS320C2800		= 0x009Du,
	MSP430			= 0x00A0u,
	TMS320C5500Plus	= 0x00A1u
};

}


#endif