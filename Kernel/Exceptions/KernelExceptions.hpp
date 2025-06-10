#pragma once
#ifndef Kernel__KernelExceptions__hpp
#define Kernel__KernelExceptions__hpp

// #Standard
#include <stdexcept>

// #Kernel
#include "Utilities\DataStreamStatus.hpp"


class DataStreamError final : public std::runtime_error {
public:
	explicit DataStreamError (DataStreamStatus status, const std::string& what)
		: runtime_error	(what)
		, status		(status)
	{
	}

	DataStreamStatus GetStatus () const { return status; }

private:
	DataStreamStatus status;
};


#endif