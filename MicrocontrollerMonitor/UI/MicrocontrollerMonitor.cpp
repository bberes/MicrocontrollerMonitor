#include "MicrocontrollerMonitor.hpp"

// #QtUI
#include "ui_MicrocontrollerMonitor.h"

// #Qt
#include <QFileDialog>

// #Communication
#include "Connection.hpp"

// #MicrocontrollerMonitor
#include "Data\Environment.hpp"
#include "UI\Connection\ConnectionWidget.hpp"
#include "UI\MonitoringView\MonitoringTab.hpp"
#include "UI\MonitoringView\ProcessorView.hpp"
#include "LoggerWidget.hpp"
#include "NewMonitoringTabDialog.hpp"
#include "RecorderWidget.hpp"
#include "SymbolsWidget.hpp"
#include "WatchWindowWidget.hpp"


static void ResetWidgetOfDockWidget (QDockWidget* dw, QWidget* w)
{
	auto old = dw->widget ();
	delete old;
	dw->setWidget (w);
}


MicrocontrollerMonitor::MicrocontrollerMonitor (LogData& logData, QWidget* parent)
	: QMainWindow		(parent)
	, ui				(std::make_unique<Ui::MicrocontrollerMonitorClass> ())
	, environment		(new Environment (logData))
	, connectionWidget	(nullptr)
	, loggerWidget		(new LoggerWidget (logData))
	, processorView		(nullptr)
	, watchWindow		(new WatchWindowWidget (environment->GetLogger ()))
	, symbolsWidget		(new SymbolsWidget (*watchWindow))
	, recorderWidget	(new RecorderWidget (*environment))
{
	ui->setupUi (this);

	watchWindow  ->setWindowTitle (QCoreApplication::translate ("MicrocontrollerMonitorClass", "Watch Window", nullptr));
	symbolsWidget->setWindowTitle (QCoreApplication::translate ("MicrocontrollerMonitorClass", "Symbols"     , nullptr));

	SetUpMenuView ();

	connectionWidget = new ConnectionWidget (*environment); // #ToDo move to ctor init list

	watchWindow->SetProtocol (environment->GetConnection ().GetProtocol ()); // #ToDo: rethink protocol access

	ResetWidgetOfDockWidget (ui->dockWidgetConnection, connectionWidget);
	ResetWidgetOfDockWidget (ui->dockWidgetLogger    , loggerWidget    );

	processorView = new ProcessorView (ui->centralWidget);
	ui->horizontalLayout->addWidget (processorView);

	QObject::connect (ui->actionNewMonitoringTab, SIGNAL (triggered ()), this, SLOT (NewMonitoringTab ()));
	QObject::connect (ui->actionOpenSymbolFile  , SIGNAL (triggered ()), this, SLOT (OpenSymbolFile   ()));
}


MicrocontrollerMonitor::~MicrocontrollerMonitor ()
{
	delete recorderWidget;
	delete connectionWidget;
	delete loggerWidget;
	delete processorView;
	delete symbolsWidget;
	delete watchWindow;
	delete environment;
}


void MicrocontrollerMonitor::SetUpMenuView ()
{
	auto actionSymbols     = symbolsWidget ->toggleViewAction ();
	auto actionWatchWindow = watchWindow   ->toggleViewAction ();
	auto actionRecorder    = recorderWidget->toggleViewAction ();

	auto actionConnection  = ui->dockWidgetConnection ->toggleViewAction ();
	auto actionTabExplorer = ui->dockWidgetTabExplorer->toggleViewAction ();
	auto actionLogger      = ui->dockWidgetLogger     ->toggleViewAction ();

	ui->menuView->addAction (actionSymbols    );
	ui->menuView->addAction (actionWatchWindow);
	ui->menuView->addAction (actionRecorder   );
	ui->menuView->addSeparator ();
	ui->menuView->addAction (actionConnection );
	ui->menuView->addAction (actionTabExplorer);
	ui->menuView->addAction (actionLogger     );

	// Retranslate UI
	actionRecorder   ->setText (QCoreApplication::translate ("MicrocontrollerMonitorClass", "Recorder"    , nullptr));

#if QT_CONFIG (shortcut)
	actionSymbols    ->setShortcut (tr ("Ctrl+S", nullptr));
	actionWatchWindow->setShortcut (tr ("Ctrl+W", nullptr));
	actionRecorder   ->setShortcut (tr ("Ctrl+R", nullptr));
	actionConnection ->setShortcut (tr ("Ctrl+Q", nullptr));
	actionTabExplorer->setShortcut (tr ("Ctrl+T", nullptr));
	actionLogger     ->setShortcut (tr ("Ctrl+L", nullptr));
#endif
}


void MicrocontrollerMonitor::customEvent (QEvent* event)
{
//	static_cast<CustomEvent*> (event)->Process ();
}


void MicrocontrollerMonitor::NewMonitoringTab ()
{
	NewMonitoringTabDialog dialog (this);
	int r = dialog.exec ();
	if (r == 0) {
		return;
	}

	// #TODO Check Input

	auto id = dialog.GetProcessorID ();
	auto index = dialog.GetTabIndex ();

	if (processorView->HasMonitoringTab (id, index)) {
		// #TODO Warning
		return;
	}

	processorView->NewMonitoringTab (environment->GetLogger (), id, index);

	auto tab = processorView->GetMonitoringTab (id, index);
	tab->SetProtocol (environment->GetConnection ().GetProtocol ());
	tab->RequestData ();
}


void MicrocontrollerMonitor::OpenSymbolFile ()
{
	QFileDialog dialog;
	dialog.setFileMode (QFileDialog::FileMode::ExistingFile);
	dialog.setViewMode (QFileDialog::ViewMode::Detail);
	dialog.setNameFilter (tr ("Symbol File (*.out)"));
	if (dialog.exec () == 0) {
		return;
	}

	auto fileNames = dialog.selectedFiles ();
	auto fileName = fileNames.first ();
	symbolsWidget->Load (fileName);
	symbolsWidget->show ();
}