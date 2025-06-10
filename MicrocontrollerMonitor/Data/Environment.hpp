#pragma once
#ifndef Data__Environment__hpp
#define Data__Environment__hpp

// #Kernel
#include "Types\Owner.hpp"
#include "KernelTypes.hpp"

// #Communication
#include "CommunicationTypes.hpp"

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"


class Environment final {
public:
	explicit Environment (LogData& logData);
	~Environment ();

	Environment (const Environment&)						= delete;
	Environment&	operator=		(const Environment&)	= delete;

	Utilities::Logger&			GetLogger			();
	Communication::Connection&	GetConnection		();

	const WatchWindow::Table&	RecorderParams		() { return *recorderParams; }

private:
	void						LoadRecorderParams	();

private:
	const Owner<EventLogger>				logger;
	const Owner<Communication::Connection>	connection;

	const Owner<WatchWindow::Table>			recorderParams;
};


#endif