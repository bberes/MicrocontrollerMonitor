#pragma once
#ifndef Communication__HiTerm_CommonParts__hpp
#define Communication__HiTerm_CommonParts__hpp

// #Kernel
#include "Types\BaseTypes.hpp"
#include "KernelTypes.hpp"

// #Communication
#include "Protocols\HiTerm\Types\MemoryEntries.hpp"
#include "CommunicationTypes.hpp"


namespace Communication::HiTerm {

size_t LengthOf (const Variables& variables);

size_t Read (DataStream& ds, Variables& variables, UInt16 length);

size_t Write (DataStream& ds, const Variables& variables);

}


namespace Communication::HiTerm::Deprecated {

size_t ReadOld  (DataStream& ds, MemoryEntries& memoryEntries, UInt16 length);
size_t WriteOld (DataStream& ds, const MemoryEntries& memoryEntries);

size_t ReadOld  (DataStream& ds, Variables& variables, UInt16 length);
size_t WriteOld (DataStream& ds, const Variables& variables);

}


#endif