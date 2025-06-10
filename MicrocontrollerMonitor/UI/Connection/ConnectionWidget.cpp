#include "ConnectionWidget.hpp"

// #QtUI
#include "ui_ConnectionWidget.h"

// #Standard
#include <stdexcept>

// #Qt
#include <QFile>

// #Kernel
#include "Utilities\Logger.hpp"

// #Communication
#include "Protocols\HiTermProtocol.hpp"
#include "Connection.hpp"

// #MicrocontrollerMonitor
#include "Data\Environment.hpp"
#include "SerialPortSettings.hpp"


static const QString configFileName (".RuntimeCache\\ConnectionDefaults.cfg");


ConnectionWidget::ConnectionWidget (Environment& environment, QWidget* parent)
	: QWidget		(parent)
	, ui			(std::make_unique<Ui::ConnectionWidgetClass> ())
	, settings		(nullptr)
	, connection	(environment.GetConnection ())
	, logger		(environment.GetLogger ())
{
	ui->setupUi (this);

	AddProtocols ();
	AddConnectionSettings (new SerialPortSettings (connection));

	ProtocolChanged ();
	ConnectionTypeChanged ();

	QObject::connect (ui->comboBoxCommunicationProtocol, SIGNAL (currentIndexChanged (int)), this, SLOT (ProtocolChanged ()));
	QObject::connect (ui->comboBoxConnectionType, SIGNAL (currentIndexChanged (int)), this, SLOT (ConnectionTypeChanged ()));

	ui->pushButtonDisconnect->setDisabled (true);
	QObject::connect (ui->pushButtonConnect, SIGNAL (released ()), this, SLOT (Connect ()));
	QObject::connect (ui->pushButtonDisconnect, SIGNAL (released ()), this, SLOT (Disconnect ()));
	QObject::connect (ui->pushButtonSetAsDefault, SIGNAL (released ()), this, SLOT (SetAsDefault ()));

	// #TODO It should be elsewhere!
	QFile config (configFileName);
	if (config.open (QIODevice::ReadOnly)) {
		DataStream ds (&config);
		LoadState (ds);
	}
}


void ConnectionWidget::SetStateOfControls (bool isConnected)
{
	ui->comboBoxCommunicationProtocol->setEnabled (!isConnected);
	ui->comboBoxConnectionType->setEnabled (!isConnected);
	settings->setEnabled (!isConnected);
	ui->pushButtonConnect->setEnabled (!isConnected);
	ui->pushButtonDisconnect->setEnabled (isConnected);
}


namespace {

const QString TextHiTerm ("HiTerm");

}


void ConnectionWidget::AddProtocols ()
{
	ui->comboBoxCommunicationProtocol->addItem (TextHiTerm);
}


void ConnectionWidget::AddConnectionSettings (ConnectionSettings* settings)
{
	QString name = settings->GetTypeName ();
	if (settingsWidgets.count (name) != 0) {
		throw std::invalid_argument ("{E713B931-6716-420D-87E8-7561905EBF07}");
	}

	settingsWidgets[name] = settings;

	ui->comboBoxConnectionType->addItem (name);
}


void ConnectionWidget::SetCurrentSettings (ConnectionSettings* settings)
{
	ui->horizontalLayoutConnection->removeWidget (this->settings);
	ui->horizontalLayoutConnection->addWidget (settings);
	this->settings = settings;
}


static const QString GUID ("{11F22BC7-9AFF-4219-813F-8E8A3C4B58D7}");


extern bool Check (int i, const QComboBox* cb); // #TODO Move into separate header


bool ConnectionWidget::LoadState (DataStream& ds)
{
	QString guid;
	int protocol = 0;
	int type = 0;

	ds >> guid;
	if (GUID != guid) {
		return false;
	}

	ds >> protocol >> type;

	if (ds.status () != DataStream::Status::Ok) {
		return false;
	}

	if (!::Check (protocol, ui->comboBoxCommunicationProtocol)) {
		return false;
	}

	if (!::Check (type, ui->comboBoxConnectionType)) {
		return false;
	}

	ui->comboBoxCommunicationProtocol->setCurrentIndex (protocol);
	ui->comboBoxConnectionType->setCurrentIndex (type);

	ProtocolChanged ();
	ConnectionTypeChanged ();

	return settings->LoadState (ds);
}


bool ConnectionWidget::StoreState (DataStream& ds) const
{
	ds << GUID << ui->comboBoxCommunicationProtocol->currentIndex () << ui->comboBoxConnectionType->currentIndex ();

	return settings->StoreState (ds);
}


void ConnectionWidget::ProtocolChanged ()
{
	auto protocol = ui->comboBoxCommunicationProtocol->currentText ();

	if (TextHiTerm == protocol) {
		connection.SetProtocol (std::make_unique<Communication::HiTermProtocol> ());
		return;
	}

	throw std::invalid_argument ("{41E73BB7-FD95-43B4-9895-498F9DBB5040}");
}


void ConnectionWidget::ConnectionTypeChanged ()
{
	auto name = ui->comboBoxConnectionType->currentText ();
	SetCurrentSettings (settingsWidgets[name]);
}


void ConnectionWidget::Connect ()
{
	if (!settings->Connect ()) {
		logger.LogWarning ("{C2E8271B-AB30-4DA3-8339-9E32D70A78F6}", "Unable to connect.");
		return;
	}

	constexpr bool isConnected = true;
	SetStateOfControls (isConnected);
}


void ConnectionWidget::Disconnect ()
{
	if (!settings->Disconnect ()) {
		logger.LogWarning ("{781112D3-C422-4840-B76E-75AFF0CCB23F}", "Unable to disconnect.");
		return;
	}

	constexpr bool isConnected = false;
	SetStateOfControls (isConnected);
}


void ConnectionWidget::SetAsDefault () const
{
	// #TODO ?
	QFile config (configFileName);
	if (config.open (QIODevice::WriteOnly)) {
		DataStream ds (&config);
		if (StoreState (ds)) {
			logger.LogInfo ("{0658DFA1-93C6-4B59-BB7F-90B467883399}", "The connection parameters have been set as default.");
		} else {
			logger.LogWarning ("{899CA1E8-E2EE-4053-95B7-B2C60E7C33BD}", "Unable to set as default.");
		}
	}
}


ConnectionWidget::~ConnectionWidget () // #ToDo: reorder functions
{
	for (auto& widget : settingsWidgets) {
		delete widget.second;
	}
}