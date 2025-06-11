#pragma once
#ifndef Kernel__Memory__hpp
#define Kernel__Memory__hpp

// #Standard
#include <type_traits>


template <class Class, typename... Args>
Class* MakeRaw (Args&&... args)
{
	static_assert (!std::is_array_v<Class>, "array type is forbidden");
	return new Class (std::forward<Args> (args)...);
}


#endif