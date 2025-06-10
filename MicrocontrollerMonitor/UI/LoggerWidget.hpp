#pragma once
#ifndef UI__LoggerWidget__hpp
#define UI__LoggerWidget__hpp

// #Qt
#include <QWidget>

// #Kernel
#include "Types\Owner.hpp"

// #MicrocontrollerMonitor
#include "Data\LogData.hpp"
#include "MicrocontrollerMonitorTypes.hpp"


class LoggerWidget final
	: public	QWidget
	, private	LogDataObserver
{
	Q_OBJECT

public:
	explicit LoggerWidget (LogData& logData, QWidget* parent = nullptr);
	~LoggerWidget ();

private:
	virtual void LineAdded (const QString& logLine) override;

private:
	Owner<Ui::LoggerWidgetClass> ui;
};


#endif