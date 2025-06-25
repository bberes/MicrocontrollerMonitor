#pragma once
#ifndef Kernel__TypeTraits__hpp
#define Kernel__TypeTraits__hpp

// #Standard
#include <algorithm>
#include <type_traits>

// #Kernel
#include "Types\BaseTypes.hpp"


template <typename T, typename From>
T InterpretAs (From src)
{
	static_assert (std::is_arithmetic_v<T> && std::is_arithmetic_v<From>);

	T value{};
	std::memcpy (&value, &src, std::min (sizeof (T), sizeof (From)));
	return value;
}


template <typename T>
T InterpretAs (const UInt8* src, size_t offset)
{
	static_assert (std::is_arithmetic_v<T>);

	T value{};
	constexpr size_t size = sizeof (T);
	std::memcpy (&value, &src[size * offset], size);
	return value;
}


#endif