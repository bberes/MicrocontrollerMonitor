#include "LoggerWidget.hpp"

// #QtUI
#include "ui_LoggerWidget.h"


LoggerWidget::LoggerWidget (LogData& logData, QWidget* parent)
	: QWidget			(parent)
	, LogDataObserver	(logData)
	, ui				(std::make_unique<Ui::LoggerWidgetClass> ())
{
	ui->setupUi (this);
}


LoggerWidget::~LoggerWidget () = default;


void LoggerWidget::LineAdded (const QString& logLine)
{
	ui->textEditLogger->append (logLine);
}