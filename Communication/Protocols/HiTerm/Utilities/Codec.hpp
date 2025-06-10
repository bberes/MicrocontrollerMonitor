#pragma once
#ifndef Communication__HiTerm_Codec__hpp
#define Communication__HiTerm_Codec__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "KernelTypes.hpp"


namespace Communication::HiTerm {

COMMUNICATION_EXPORT
ByteArray Encode (const ByteArray& byteArray);

COMMUNICATION_EXPORT
ByteArray Decode (const ByteArray& byteArray);

}


#endif