#pragma once
#ifndef Kernel__Serializable__hpp
#define Kernel__Serializable__hpp

// #Kernel
#include "KernelTypes.hpp"


class Serializable {
private:
	virtual size_t Write (DataStream& ds) const = 0;
};


#endif