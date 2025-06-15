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

	WatchWindowTableModel&		GetWWTableModel		() { return *wwTableModel; }
	const WatchWindow::Table&	RecorderParams		() { return *recorderParams; }

private:
	void						LoadTableModel		();
	void						StoreTableModel		() const;

	void						LoadRecorderParams	();

private:
	const Owner<EventLogger>				logger;
	const Owner<Communication::Connection>	connection;

	const Owner<WatchWindowTableModel>		wwTableModel;
	// #ToDo: only its table should be here (WW::Table), make it observable,
	//        class WWTM should be an observer and should be moved back into WWW.

	const Owner<WatchWindow::Table>			recorderParams;
};


#endif