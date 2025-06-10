#include "SerialPortProvider.hpp"

// #Standard
#include <stdexcept>

// #Qt
#include <QSerialPort>

// #Network
#include "Exceptions\SerialPortExceptions.hpp"
#include "Utilities\SerialPortDescriptor.hpp"


class Network::SerialPortProvider::Impl final {
public:
	Impl (const SerialPort::Descriptor& d);

	void		Set			(const SerialPort::Descriptor&);
	void		Connect		();
	void		Disconnect	();
	QIODevice&	IODevice	();
	bool		HasError	() const;

private:
	QSerialPort serialPort;
};


Network::SerialPortProvider::Impl::Impl (const SerialPort::Descriptor& d)
{
	Set (d);
}


namespace {

qint32 ToQBaudRate (Int32 br)
{
	switch (br) {
	case Network::SerialPort::BR_1200:		return QSerialPort::Baud1200;
	case Network::SerialPort::BR_2400:		return QSerialPort::Baud2400;
	case Network::SerialPort::BR_4800:		return QSerialPort::Baud4800;
	case Network::SerialPort::BR_9600:		return QSerialPort::Baud9600;
	case Network::SerialPort::BR_19200:		return QSerialPort::Baud19200;
	case Network::SerialPort::BR_38400:		return QSerialPort::Baud38400;
	case Network::SerialPort::BR_57600:		return QSerialPort::Baud57600;
	case Network::SerialPort::BR_115200:	return QSerialPort::Baud115200;
	default:
		return br;
	}
}

QSerialPort::DataBits ToQDataBits (Network::SerialPort::DataBits db)
{
	switch (db) {
	case Network::SerialPort::DataBits::DB_5:	return QSerialPort::Data5;
	case Network::SerialPort::DataBits::DB_6:	return QSerialPort::Data6;
	case Network::SerialPort::DataBits::DB_7:	return QSerialPort::Data7;
	case Network::SerialPort::DataBits::DB_8:	return QSerialPort::Data8;
	default:
		throw std::invalid_argument ("{DB6D7EFB-4930-4DB6-80B8-F52ACBE7ED31}");
	}
}

QSerialPort::StopBits ToQStopBits (Network::SerialPort::StopBits sb)
{
	switch (sb) {
	case Network::SerialPort::StopBits::One:		return QSerialPort::OneStop;
	case Network::SerialPort::StopBits::OneAndHalf:	return QSerialPort::OneAndHalfStop;
	case Network::SerialPort::StopBits::Two:		return QSerialPort::TwoStop;
	default:
		throw std::invalid_argument ("{EA8F2B28-5A9D-4354-801C-740140DF8682}");
	}
}

QSerialPort::Parity ToQParity (Network::SerialPort::Parity p)
{
	switch (p) {
	case Network::SerialPort::Parity::No:		return QSerialPort::NoParity;
	case Network::SerialPort::Parity::Even:		return QSerialPort::EvenParity;
	case Network::SerialPort::Parity::Odd:		return QSerialPort::OddParity;
	case Network::SerialPort::Parity::Space:	return QSerialPort::SpaceParity;
	case Network::SerialPort::Parity::Mark:		return QSerialPort::MarkParity;
	default:
		throw std::invalid_argument ("{829A71D4-83C4-415C-B8B0-6D97470A4CBF}");
	}
}

QSerialPort::FlowControl ToQFlowControl (Network::SerialPort::FlowControl fc)
{
	switch (fc) {
	case Network::SerialPort::FlowControl::No:			return QSerialPort::NoFlowControl;
	case Network::SerialPort::FlowControl::Hardware:	return QSerialPort::HardwareControl;
	case Network::SerialPort::FlowControl::Software:	return QSerialPort::SoftwareControl;
	default:
		throw std::invalid_argument ("{21946109-7566-4290-8A11-DC510CA2CCFF}");
	}
}

}


void Network::SerialPortProvider::Impl::Set (const SerialPort::Descriptor& d)
{
	serialPort.setPortName		(QString::fromStdString (d.portName));
	serialPort.setBaudRate		(ToQBaudRate	(d.baudRate));
	serialPort.setDataBits		(ToQDataBits	(d.dataBits));
	serialPort.setStopBits		(ToQStopBits	(d.stopBits));
	serialPort.setParity		(ToQParity		(d.parity));
	serialPort.setFlowControl	(ToQFlowControl	(d.flowControl));
}


static Network::SerialPort::ErrorCode ToErrorCode (QSerialPort::SerialPortError error)
{
	using Network::SerialPort::ErrorCode;
	switch (error) {
	case QSerialPort::NoError:						return ErrorCode::NoError;
	case QSerialPort::DeviceNotFoundError:			return ErrorCode::DeviceNotFound;
	case QSerialPort::PermissionError:				return ErrorCode::Permission;
	case QSerialPort::OpenError:					break;
	case QSerialPort::WriteError:					break;
	case QSerialPort::ReadError:					break;
	case QSerialPort::ResourceError:				break;
	case QSerialPort::UnsupportedOperationError:	return ErrorCode::UnsupportedOperation;
	case QSerialPort::UnknownError:					break;
	case QSerialPort::TimeoutError:					break;
	case QSerialPort::NotOpenError:					break;
	default:
		break;
	}
	throw std::invalid_argument ("{665EB379-EBB0-4D1A-8B42-772DB697513E}");
}


void Network::SerialPortProvider::Impl::Connect ()
{
	bool r = serialPort.open (QIODevice::OpenModeFlag::ReadWrite);
	if (!r) {
		auto e = serialPort.error ();
		auto s = serialPort.errorString ();
		throw SerialPort::ConnectError (ToErrorCode (e), s.toStdString ());
	}
}


void Network::SerialPortProvider::Impl::Disconnect ()
{
	serialPort.close ();
}


QIODevice& Network::SerialPortProvider::Impl::IODevice ()
{
	return serialPort;
}


bool Network::SerialPortProvider::Impl::HasError () const
{
	return serialPort.error () != QSerialPort::SerialPortError::NoError;
}


Network::SerialPortProvider::SerialPortProvider (const SerialPort::Descriptor& d)
	: impl (std::make_unique<Impl> (d))
{
}


Network::SerialPortProvider::~SerialPortProvider () = default;


void Network::SerialPortProvider::Set (const SerialPort::Descriptor& d)
{
	impl->Set (d);
}


void Network::SerialPortProvider::Connect ()
{
	impl->Connect ();
}


void Network::SerialPortProvider::Disconnect ()
{
	impl->Disconnect ();
}


QIODevice& Network::SerialPortProvider::IODevice ()
{
	return impl->IODevice ();
}


bool Network::SerialPortProvider::HasError () const
{
	return impl->HasError ();
}