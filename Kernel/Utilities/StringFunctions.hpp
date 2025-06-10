#pragma once
#ifndef Kernel__Utilities_StringFunctions__hpp
#define Kernel__Utilities_StringFunctions__hpp

// #ExportHeader
#include "KernelExport.hpp"

// #Standard
#include <string>

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Utilities {

constexpr UInt32 UInt32MAX = std::numeric_limits<UInt32>::max ();

KERNEL_EXPORT
std::string BytesToString (const UInt8* const bytes, const UInt32 size = UInt32MAX);

}


#endif