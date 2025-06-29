#include "MonitoringTab.hpp"

// #QtUI
#include "ui_MonitoringTab.h"

// #Qt
#include <QTimer>

// #Communication
#include "Requests\TabDataRequest.hpp"
#include "Requests\TabValuesRequest.hpp"
#include "CommunicationProtocol.hpp"

// #MicrocontrollerMonitor
#include "Data\MonitoringTabTableModel.hpp"
#include "CustomEvent.hpp"
#include "Utilities.hpp"


MonitoringTab::MonitoringTab (Int32 processorID, Int32 tabIndex, QWidget* parent)
	: QWidget		(parent)
	, ui			(std::make_unique<Ui::MonitoringTabClass> ())
	, processorID	(processorID)
	, tabIndex		(tabIndex)
	, tableModel	(nullptr)
	, timer			(MakeChild<QTimer> (*this))
	, protocol		(nullptr)
{
	ui->setupUi (this);

	tableModel = MakeChild<MonitoringTabTableModel> (*ui->tableView);
	ui->tableView->setModel (tableModel);

	AutoRefresh (false);
	connect (ui->spinBox   , &QSpinBox::valueChanged, this, &MonitoringTab::ChangeRate   );
	connect (ui->checkBox  , &QCheckBox::toggled    , this, &MonitoringTab::AutoRefresh  );
	connect (ui->pushButton, &QPushButton::pressed  , this, &MonitoringTab::RequestValues);
	connect (timer         , &QTimer::timeout       , this, &MonitoringTab::RequestValues);
}


MonitoringTab::~MonitoringTab () = default;


void MonitoringTab::SetProtocol (Communication::Protocol& protocol)
{
	this->protocol = &protocol;
}


void MonitoringTab::ChangeRate ()
{
	AutoRefresh (true);
}


void MonitoringTab::AutoRefresh (bool autoRefresh)
{
	if (autoRefresh) {
		ui->pushButton->setEnabled (false);
		ui->spinBox   ->setEnabled (true );
		timer->setInterval (ui->spinBox->value ());
		timer->start ();
	} else {
		ui->pushButton->setEnabled (true );
		ui->spinBox   ->setEnabled (false);
		timer->stop ();
	}
}


void MonitoringTab::RequestData ()
{
	protocol->AddListener (static_cast<Communication::TabDataResponseListener&> (*tableModel));
	QCoreApplication::postEvent (this, MakeEvent<CustomEvent> ([this] () {
		protocol->SendRequest (Communication::TabDataRequest (processorID, tabIndex));
	}));
}


void MonitoringTab::RequestValues ()
{
	protocol->AddListener (static_cast<Communication::TabValuesResponseListener&> (*tableModel));
	QCoreApplication::postEvent (this, MakeEvent<CustomEvent> ([this] () {
		protocol->SendRequest (Communication::TabValuesRequest (processorID, tabIndex));
	}));
}


void MonitoringTab::customEvent (QEvent* event)
{
	static_cast<CustomEvent*> (event)->Process ();
}