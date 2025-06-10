#pragma once
#ifndef Communication__TabDataEntry__hpp
#define Communication__TabDataEntry__hpp

// #Standard
#include <string>

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication {

struct TabDataEntry final {
	std::string	name;
	std::string	unit;
	UInt16		type;
	UInt32		ptr;
	UInt32		pMax;
	UInt32		pMin;
};

}


#endif