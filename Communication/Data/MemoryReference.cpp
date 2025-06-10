#include "MemoryReference.hpp"

// #Standard
#include <stdexcept>


void Communication::MemoryReference::CheckAddressSize (size_t size) const
{
	if (static_cast<size_t> (addressSize) != size) {
		throw std::invalid_argument ("{E040673F-60D9-49E1-AFB8-6B8DA09B41E2}");
	}
}