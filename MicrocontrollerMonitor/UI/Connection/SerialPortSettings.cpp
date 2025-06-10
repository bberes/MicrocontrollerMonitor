#include "SerialPortSettings.hpp"

// #QtUI
#include "ui_SerialPortSettings.h"

// #Qt
#include <QMessageBox>

// #Network
#include "Exceptions\SerialPortExceptions.hpp"
#include "IODeviceProviders\SerialPortProvider.hpp"
#include "Utilities\SerialPortDescriptor.hpp"

// #Communication
#include "Connection.hpp"


namespace {

const QString TextCustom ("Custom");


bool IsCustomBaudRateSelected (Ui::SerialPortSettingsClass& ui)
{
	return ui.comboBoxBaudRate->currentText () == TextCustom;
}

}


SerialPortSettings::SerialPortSettings (Communication::Connection& connection, QWidget* parent)
	: ConnectionSettings	(parent)
	, ui					(std::make_unique<Ui::SerialPortSettingsClass> ())
	, intValidator			(new QIntValidator (this)) // #ToDo: use fn. to enforce passing parent on creation: Create<QIntValidator> (this)
	, connection			(connection)
{
	ui->setupUi (this);
	intValidator->setBottom (1);

	SetUpBaudRate		();
	SetUpDataBits		();
	SetUpParity			();
	SetUpStopBits		();
	SetUpFlowControl	();
}


SerialPortSettings::~SerialPortSettings () = default;


QString SerialPortSettings::GetTypeName () const
{
	return "Serial Port"; // #ToDo: translations (review functions too!)
}


static bool CheckInput (Ui::SerialPortSettingsClass& ui)
{
	QString info;

	if (ui.lineEditPortName->text ().isEmpty ()) {
		info += " - Port Name is missing\n";
	}

	if (IsCustomBaudRateSelected (ui)) {
		if (ui.lineEditBaudRateCustom->text ().isEmpty ()) {
			info += " - Custom Baud Rate is missing\n";
		}
	}

	if (info.isEmpty ()) {
		return true;
	}

	QMessageBox mb;
	mb.setIcon (QMessageBox::Warning);
	mb.setWindowTitle ("Missing Input");
	mb.setText ("All fields are required to be filled correctly.");
	mb.setInformativeText (info);
	mb.setStandardButtons (QMessageBox::Ok);
	mb.exec ();

	return false;
}


static Network::SerialPort::Descriptor GetDescriptor (Ui::SerialPortSettingsClass& ui)
{
	using namespace Network::SerialPort;

	Int32 baudRate = 0;
	if (IsCustomBaudRateSelected (ui)) {
		baudRate = ui.lineEditBaudRateCustom->text ().toInt ();
	} else {
		baudRate = ui.comboBoxBaudRate->currentData ().value<BaudRate> ();
	}

	Descriptor descriptor;
	descriptor.portName		= ui.lineEditPortName->text ().toStdString ();
	descriptor.baudRate		= baudRate;
	descriptor.dataBits		= ui.comboBoxDataBits->currentData ().value<DataBits> ();
	descriptor.stopBits		= ui.comboBoxStopBits->currentData ().value<StopBits> ();
	descriptor.parity		= ui.comboBoxParity->currentData ().value<Parity> ();
	descriptor.flowControl	= ui.comboBoxFlowControl->currentData ().value<FlowControl> ();

	return descriptor;
}


static void UnableToConnect (std::string info)
{
	QMessageBox mb;
	mb.setIcon (QMessageBox::Warning);
	mb.setWindowTitle ("Connection");
	mb.setText ("Unable to connect!");
	mb.setInformativeText (QString::fromStdString (info));
	mb.setStandardButtons (QMessageBox::Ok);
	mb.exec ();
}


bool SerialPortSettings::Connect ()
{
	if (!CheckInput (*ui)) {
		return false;
	}

	auto descriptor = GetDescriptor (*ui);
	connection.Reset (std::make_unique<Network::SerialPortProvider> (descriptor));

	try {
		connection.Connect ();
	} catch (const Network::SerialPort::ConnectError& error) {
		auto e = error.GetErrorCode ();
		auto m = error.what ();
		UnableToConnect (m);
		return false;
	}

	return true;
}


bool SerialPortSettings::Disconnect ()
{
	connection.Disconnect ();

	return true;
}


bool Check (int i, const QComboBox* cb)
{
	return i >= 0 || i < cb->count ();
}


namespace {

class State final {
public:
	State (Ui::SerialPortSettingsClass& ui)
		: port	(ui.lineEditPortName		->text ())
		, cbr	(ui.lineEditBaudRateCustom	->text ())
		, br	(ui.comboBoxBaudRate		->currentIndex ())
		, db	(ui.comboBoxDataBits		->currentIndex ())
		, py	(ui.comboBoxParity			->currentIndex ())
		, sb	(ui.comboBoxStopBits		->currentIndex ())
		, fc	(ui.comboBoxFlowControl		->currentIndex ())
	{
	}

	bool Check (const Ui::SerialPortSettingsClass& ui) const
	{
		if (!::Check (br, ui.comboBoxBaudRate) ||
			!::Check (db, ui.comboBoxDataBits) ||
			!::Check (py, ui.comboBoxParity  ) ||
			!::Check (sb, ui.comboBoxStopBits) ||
			!::Check (fc, ui.comboBoxFlowControl))
		{
			return false;
		}

		return true;
	}

	void SetUI (Ui::SerialPortSettingsClass& ui) const
	{
		ui.lineEditPortName			->setText (port);
		ui.lineEditBaudRateCustom	->setText (cbr);
		ui.comboBoxBaudRate			->setCurrentIndex (br);
		ui.comboBoxDataBits			->setCurrentIndex (db);
		ui.comboBoxParity			->setCurrentIndex (py);
		ui.comboBoxStopBits			->setCurrentIndex (sb);
		ui.comboBoxFlowControl		->setCurrentIndex (fc);
	}

	void Load (DataStream& ds);
	void Store (DataStream& ds) const;

private:
	QString port;
	QString	cbr;
	int		br;
	int		db;
	int		py;
	int		sb;
	int		fc;
};


void State::Store (DataStream& ds) const
{
	ds << port << cbr << br << db << py << sb << fc;
}


void State::Load (DataStream& ds)
{
	ds >> port >> cbr >> br >> db >> py >> sb >> fc;
}


const QString GUID ("{7207B713-253A-42A3-AB96-92F3C8F0DA36}");

}


bool SerialPortSettings::LoadState (DataStream& ds)
{
	QString guid;
	State state (*ui);

	ds >> guid;
	if (GUID != guid) {
		return false;
	}
	
	state.Load (ds);

	bool result = ds.status () == DataStream::Status::Ok && state.Check (*ui);
	if (result) {
		state.SetUI (*ui);
		BaudRateChanged ();
	}

	return result;
}


bool SerialPortSettings::StoreState (DataStream& ds) const
{
	ds << GUID;

	State (*ui).Store (ds);

	return ds.status () == DataStream::Status::Ok;
}


void SerialPortSettings::SetUpBaudRate ()
{
	using namespace Network::SerialPort;
	auto values = {
		BR_1200,
		BR_2400,
		BR_4800,
		BR_9600,
		BR_19200,
		BR_38400,
		BR_57600,
		BR_115200
	};
	for (auto value : values) {
		ui->comboBoxBaudRate->addItem (QString::number (value), value);
	}
	ui->comboBoxBaudRate->addItem (TextCustom);

	ui->lineEditBaudRateCustom->setValidator (intValidator);

	BaudRateChanged ();

	QObject::connect (ui->comboBoxBaudRate, SIGNAL (currentIndexChanged (int)), this, SLOT (BaudRateChanged ()));
}


void SerialPortSettings::SetUpDataBits ()
{
	using namespace Network::SerialPort;
	auto values = {
		DataBits::DB_5,
		DataBits::DB_6,
		DataBits::DB_7,
		DataBits::DB_8
	};
	for (auto value : values) {
		auto v = static_cast<Int32> (value);
		ui->comboBoxDataBits->addItem (QString::number (v), v);
	}
}


void SerialPortSettings::SetUpParity ()
{
	using namespace Network::SerialPort;
	auto values = {
		std::pair ("No Parity",	Parity::No),
		std::pair ("Even",		Parity::Even),
		std::pair ("Odd",		Parity::Odd),
		std::pair ("Space",		Parity::Space),
		std::pair ("Mark",		Parity::Mark)
	};
	size_t i = 0u;
	for (auto value : values) {
		auto v = static_cast<Int32> (value.second);
		ui->comboBoxParity->addItem (value.first, v);
	}
}


void SerialPortSettings::SetUpStopBits ()
{
	using namespace Network::SerialPort;
	auto values = {
		std::pair ("1",		StopBits::One),
		std::pair ("1.5",	StopBits::OneAndHalf),
		std::pair ("2",		StopBits::Two)
	};
	for (auto value : values) {
		auto v = static_cast<Int32> (value.second);
		ui->comboBoxStopBits->addItem (value.first, v);
	}
}


void SerialPortSettings::SetUpFlowControl ()
{
	using namespace Network::SerialPort;
	auto values = {
		std::pair ("No Flow Control",	FlowControl::No),
		std::pair ("Hardware Control",	FlowControl::Hardware),
		std::pair ("Software Control",	FlowControl::Software)
	};
	for (auto value : values) {
		auto v = static_cast<Int32> (value.second);
		ui->comboBoxFlowControl->addItem (value.first, v);
	}
}


void SerialPortSettings::BaudRateChanged ()
{
	const bool isCustom = IsCustomBaudRateSelected (*ui);
	ui->lineEditBaudRateCustom->setEnabled (isCustom);
	if (isCustom) {
		ui->lineEditBaudRateCustom->setText ("");
	} else {
		ui->lineEditBaudRateCustom->setText ("Select Custom to Edit");
	}
}