#pragma once
#ifndef Kernel__Utilities_CRC__hpp
#define Kernel__Utilities_CRC__hpp

// #ExportHeader
#include "KernelExport.hpp"

// #Kernel
#include "Types\BaseTypes.hpp"
#include "KernelTypes.hpp"


namespace Utilities {

KERNEL_EXPORT
UInt16 FastCRC16 (const ByteArray& data);

KERNEL_EXPORT
UInt16 CalcCRC16 (const ByteArray& data);

}


#endif