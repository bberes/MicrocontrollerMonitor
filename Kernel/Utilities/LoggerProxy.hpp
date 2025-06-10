#pragma once
#ifndef Kernel__Utilities_LoggerProxy__hpp
#define Kernel__Utilities_LoggerProxy__hpp

// #Kernel
#include "Logger.hpp"


namespace Utilities {

class KERNEL_EXPORT LoggerProxy final : public Logger {
public:
	LoggerProxy ();
	virtual ~LoggerProxy () override;

	void			SetLogger	(Logger* logger);

	virtual void	SetLogLevel	(LogLevel level) override;

	virtual void	LogInfo		(const std::string& guid, const std::string& m) override;
	virtual void	LogWarning	(const std::string& guid, const std::string& w, const std::exception* ex = nullptr) override;
	virtual void	LogError	(const std::string& guid, const std::string& e, const std::exception* ex = nullptr) override;

private:
	Logger* logger;
};

}


#endif