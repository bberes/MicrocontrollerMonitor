#include "Environment.hpp"

// #Qt
#include <QFile>
#include <QVariant>

// #Kernel
#include "Utilities\Debug.hpp"

// #Communication
#include "Connection.hpp"

// #MicrocontrollerMonitor
#include "EventLogger.hpp"
#include "WatchWindowTable.hpp"


Environment::Environment (LogData& logData)
	: logger			(std::make_unique<EventLogger>					(logData, Utilities::LogLevel::Info)) // #ToDo: make log level adjustable (i.e. with UI control)
	, connection		(std::make_unique<Communication::Connection>	(*logger))
	, recorderParams	(std::make_unique<WatchWindow::Table>			())
{
	LoadRecorderParams ();
}


Environment::~Environment () = default;


Utilities::Logger& Environment::GetLogger ()
{
	return *logger;
}


Communication::Connection& Environment::GetConnection ()
{
	return *connection;
}


void Environment::LoadRecorderParams () // #ToDo
{
	static const QString configFileName (".RuntimeCache\\RecorderParameters.cfg");

	QFile config (configFileName);
	if (!config.open (QIODevice::ReadOnly)) {
		return;
	}

	DataStream ds (&config);
	QString guid;
	ds >> guid;
	if (guid != QString ("{12C1DA00-0418-4BD5-AF68-32FFB4E85A8E}")) {
		return; // #ToDo: report warning / error
	}

	auto& params = *recorderParams;
	params.Load (ds);
	if (params.RowCount () != 15u) {
		TODO;
	}

	// #ToDo
	params.SetData (0x00, QString ("0xE8AC"));	// val_addr[0]
	params.SetData (0x01, QString ("0xE8AE"));	// val_addr[1]
	params.SetData (0x02, QString (     "0"));	// val_addr[2]
	params.SetData (0x03, QString (     "0"));	// val_addr[3]
	params.SetData (0x04, QString (     "0"));	// sampled_date
	params.SetData (0x05, QString (     "0"));	// sampled_time
	params.SetData (0x06, QString (     "3"));	// sample_time
	params.SetData (0x07, QString (     "0"));	// trig_level
	params.SetData (0x08, QString (     "0"));	// start_idx
	params.SetData (0x09, QString (     "0"));	// trigger_ch
	params.SetData (0x0A, QString (  "0x80"));	// pretrigger
	params.SetData (0x0B, QString (     "0"));	// trig_slope
	params.SetData (0x0C, QString (     "1"));	// tnow
	params.SetData (0x0D, QString (     "8"));	// tlevel_type
	params.SetData (0x0E, QString (     "1"));	// state
}