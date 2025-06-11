#pragma once
#ifndef MicrocontrollerMonitorTypes__hpp
#define MicrocontrollerMonitorTypes__hpp

// #Qt
#include "qtconfigmacros.h"


class QEvent;
class QIntValidator;
class QLabel;
class QModelIndex;
class QObject;
class QPlainTextEdit;
class QString;
class QWidget;


class ArrayListener;
class ConnectionSettings;
class Environment;
class EventLogger;
class LogData;
class LoggerWidget;
class MonitoringTab;
class MonitoringTabTableModel;
class ParamsListener;
class ProcessorTab;
class ProcessorView;
class RecorderWidget;
class StateListener;
class SymbolsWidget;
class WatchWindowTableModel;
class WatchWindowWidget;
class WriteListener;


namespace WatchWindow {
	class Table; // #ToDo: rename `WatchWindow::Table` to `VariableTable` ???
}


QT_BEGIN_NAMESPACE
namespace Ui {
	class ConnectionWidgetClass;
	class LoggerWidgetClass;
	class MicrocontrollerMonitorClass;
	class MonitoringTabClass;
	class NewMonitoringTabDialogClass;
	class ProcessorTabClass;
	class ProcessorViewClass;
	class RecorderWidget;
	class SerialPortSettingsClass;
	class SymbolsWidgetClass;
	class WatchWindowWidgetClass;
};
QT_END_NAMESPACE


#endif