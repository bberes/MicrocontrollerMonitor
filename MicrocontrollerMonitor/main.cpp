// #Qt
#include <QtWidgets\QApplication>

// #Kernel
#include "Utilities\Debug.hpp"

// #MicrocontrollerMonitor
#include "Data\LogData.hpp"
#include "UI\CrashReportDialog.hpp"
#include "UI\MicrocontrollerMonitor.hpp"


#ifdef DEBUG_MODE
static QString ToString (const NoImplementation&);
#endif
static QString ToString (const KnownProblem&   e) { return e.guid;    }
static QString ToString (const std::exception& e) { return e.what (); }

static int ReportError (LogData& logData, const QString& details = {});


int main (int argc, char* argv[])
{
	LogData logData;
	QApplication a (argc, argv);

	try {
		MicrocontrollerMonitor w (logData);
		w.show ();
		return a.exec ();
	}
#ifdef DEBUG_MODE
	catch (NoImplementation& e)	{ return ReportError (logData, ToString (e)); }
#endif
	catch (KnownProblem&     e)	{ return ReportError (logData, ToString (e)); }
	catch (std::exception&   e)	{ return ReportError (logData, ToString (e)); }
	catch (...)					{ return ReportError (logData);				  }
}


static int ReportError (LogData& logData, const QString& details/* = {}*/)
{
	logData.Append ("Fatal exception occured.");
	if (!details.isEmpty ()) {
		logData.Append (QString ("Details: ") + details);
	}

	CrashReportDialog dialog;
	DEBUG_ONLY (dialog.SetDebugText (details));
	const int r = dialog.exec ();

	const QString userInput = dialog.GetUserInput ();
	if (!userInput.isEmpty ()) {
		logData.Append ("User Input:");
		logData.Append (userInput);
	}

	logData.Store ();
	return r;
}


#ifdef DEBUG_MODE
static QString ToString (const NoImplementation& ni)
{
	QString text;
	if (ni.guid != nullptr) {
		text.append (QString ("GUID: ") + ni.guid + "\n");
	}
	const QString file (ni.file);
	const QString mm ("MicrocontrollerMonitor");
	const QString sub = file.mid (file.indexOf (mm) + mm.length ());
	text.append (QString ("File: %MiMoSourceRootDir%") + sub + "\n");
	text.append (QString ("Line: ") + QString::number (ni.line));
	return text;
}
#endif