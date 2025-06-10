#pragma once
#ifndef Kernel__Owner__hpp
#define Kernel__Owner__hpp

// #Standard
#include <memory>


template <typename Type>
using Owner = std::unique_ptr<Type>;


#endif