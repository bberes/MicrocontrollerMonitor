#pragma once
#ifndef UI__SerialPortSettings__hpp
#define UI__SerialPortSettings__hpp

// #Kernel
#include "Types\Owner.hpp"

// #Communication
#include "CommunicationTypes.hpp"

// #MicrocontrollerMonitor
#include "ConnectionSettings.hpp"
#include "MicrocontrollerMonitorTypes.hpp"


class SerialPortSettings : public ConnectionSettings {
	Q_OBJECT

public:
	explicit SerialPortSettings (Communication::Connection& connection, QWidget* parent = nullptr);
	~SerialPortSettings ();

private:
	virtual QString	GetTypeName	() const override;
	virtual bool	Connect		() override;
	virtual bool	Disconnect	() override;

	virtual bool	LoadState	(DataStream& ds) override;
	virtual bool	StoreState	(DataStream& ds) const override;

private:
	void SetUpBaudRate		();
	void SetUpDataBits		();
	void SetUpParity		();
	void SetUpStopBits		();
	void SetUpFlowControl	();

private slots:
	void BaudRateChanged	();

private:
	Owner<Ui::SerialPortSettingsClass>	ui;

	QIntValidator*						intValidator;

	Communication::Connection&			connection;
};


#endif