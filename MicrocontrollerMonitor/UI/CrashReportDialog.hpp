#pragma once
#ifndef UI__CrashReportDialog__hpp
#define UI__CrashReportDialog__hpp

// #Qt
#include <QDialog>

// #Kernel
#include "Utilities\Debug.hpp"

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"


class CrashReportDialog final : public QDialog {
	Q_OBJECT

public:
	explicit CrashReportDialog (QWidget* parent = nullptr);

	QString GetUserInput () const;

	DEBUG_ONLY (void SetDebugText (const QString& text));

private:
	QPlainTextEdit*	inputBox;
	DEBUG_ONLY (QLabel* debugLabel);
};


#endif