#pragma once
#ifndef Kernel__Utilities_Logger__hpp
#define Kernel__Utilities_Logger__hpp

// #ExportHeader
#include "KernelExport.hpp"

// #Standard
#include <string>

// #Kernel
#include "LogLevel.hpp"


namespace Utilities {

class KERNEL_EXPORT Logger {
public:
	virtual ~Logger ();

	virtual void	SetLogLevel	(LogLevel) = 0;

	virtual void	LogInfo		(const std::string& guid, const std::string& m) = 0;
	virtual void	LogWarning	(const std::string& guid, const std::string& w, const std::exception* ex = nullptr) = 0;
	virtual void	LogError	(const std::string& guid, const std::string& e, const std::exception* ex = nullptr) = 0;
};

}


#endif