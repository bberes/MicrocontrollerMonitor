#pragma once
#ifndef Data__EventLogger__hpp
#define Data__EventLogger__hpp

// #Kernel
#include "Utilities\Logger.hpp"

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"


class EventLogger final : public Utilities::Logger {
public:
	using LogLevel = Utilities::LogLevel;

	explicit EventLogger (LogData& data, LogLevel level);
	virtual ~EventLogger () override;

	virtual void	SetLogLevel	(LogLevel level) override;

	virtual void	LogInfo		(const std::string& guid, const std::string& m) override;
	virtual void	LogWarning	(const std::string& guid, const std::string& w, const std::exception* ex = nullptr) override;
	virtual void	LogError	(const std::string& guid, const std::string& e, const std::exception* ex = nullptr) override;

private:
	LogData&	data;
	LogLevel	level;
};


#endif