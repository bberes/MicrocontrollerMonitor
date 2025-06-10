#include "EventLogger.hpp"

// #Qt
#include <QDateTime>
#include <QString>

// #MicrocontrollerMonitor
#include "LogData.hpp"


EventLogger::EventLogger (LogData& data, LogLevel level)
	: data	(data)
	, level	(level)
{
}


EventLogger::~EventLogger () = default;


void EventLogger::SetLogLevel (LogLevel level)
{
	this->level = level;
}


namespace {

std::string Details (const std::exception* ex)
{
	if (ex == nullptr) {
		return std::string ();
	}
	return "\n\tDetails: " + std::string (ex->what ());
}


struct Settings {
	bool showGUID = true;
};


QString Log (const Settings& s, const char* title, const std::string& guid, const std::string& m, const std::exception* ex)
{
	std::string log;
	if (s.showGUID) {
		log += guid + " ";
	}
	log += std::string (title) + ": " + m + Details (ex);

	QString time = QDateTime::currentDateTime ().toString (Qt::ISODateWithMs);
	return time + " " + QString::fromStdString (log);
}

}


void EventLogger::LogInfo (const std::string& guid, const std::string& m)
{
	if (level > LogLevel::Info) {
		return;
	}

	Settings s;
	s.showGUID = false;
	data.Append (Log (s, "INFO", guid, m, nullptr));
}


void EventLogger::LogWarning (const std::string& guid, const std::string& w, const std::exception* ex)
{
	if (level > LogLevel::Warning) {
		return;
	}

	data.Append (Log (Settings (), "WARNING", guid, w, ex));
}


void EventLogger::LogError (const std::string& guid, const std::string& e, const std::exception* ex)
{
	if (level > LogLevel::Error) {
		return;
	}

	data.Append (Log (Settings (), "ERROR", guid, e, ex));
}