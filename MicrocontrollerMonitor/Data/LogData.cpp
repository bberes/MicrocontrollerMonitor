#include "LogData.hpp"

// #Qt
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QUuid>


void LogData::Append (const QString& logLine)
{
	lines.push_back (logLine);
	for (auto& observer : GetObservers ()) {
		static_cast<LogDataObserver*> (observer)->LineAdded (logLine);
	}
}


static void EnsureDirectory (const QString& dirName)
{
	QDir dir (dirName);
	if (!dir.exists ()) {
		dir.mkpath (".");
	}
}


static QString GetUniqueFileNameWithPath (const QString& dirName)
{
	const QUuid uuid = QUuid::createUuid ();
	const QString fileName = uuid.toString (QUuid::WithoutBraces);
	return dirName + "\\" + fileName + ".log";
}


void LogData::Store () const
{
	const QString dirName ("Logs");
	EnsureDirectory (dirName);

	QFile file (GetUniqueFileNameWithPath (dirName));
	file.open (QIODevice::WriteOnly | QIODevice::Text);

	QTextStream ts (&file);
	for (auto& line : lines) {
		ts << line << '\n';
	}
}


LogDataObserver::LogDataObserver (LogData& logData)
{
	logData.Attach (*this);
}