#pragma once
#ifndef Kernel__HashTable__hpp
#define Kernel__HashTable__hpp

// #Standard
#include <unordered_map>


template <typename Key, typename Value>
using HashTable = std::unordered_map<Key, Value>;


#endif