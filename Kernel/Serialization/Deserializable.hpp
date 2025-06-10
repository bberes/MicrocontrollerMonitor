#pragma once
#ifndef Kernel__Deserializable__hpp
#define Kernel__Deserializable__hpp

// #Kernel
#include "KernelTypes.hpp"


class RegularSelector			final {};
class DeserializationSelector	final {};


class Deserializable {
protected:
	constexpr Deserializable (RegularSelector)			{}
	constexpr Deserializable (DeserializationSelector)	{}

private:
	virtual size_t Read (DataStream& ds) = 0;
};


constexpr RegularSelector			RegularConstructor;
constexpr DeserializationSelector	ForDeserialization;


#endif