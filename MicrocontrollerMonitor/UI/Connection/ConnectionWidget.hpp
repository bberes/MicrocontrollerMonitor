#pragma once
#ifndef UI__ConnectionWidget__hpp
#define UI__ConnectionWidget__hpp

// #Qt
#include <QWidget>

// #Kernel
#include "Types\HashTable.hpp"
#include "Types\Owner.hpp"
#include "KernelTypes.hpp"

// #Communication
#include "CommunicationTypes.hpp"

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"


class ConnectionWidget final : public QWidget {
	Q_OBJECT

public:
	explicit ConnectionWidget (Environment& environment, QWidget* parent = nullptr);
	~ConnectionWidget ();

private:
	void	SetStateOfControls		(bool isConnected);
	void	AddProtocols			();
	void	AddConnectionSettings	(Owner<ConnectionSettings> settings);
	void	SetCurrentSettings		(ConnectionSettings& settings);

	bool	LoadState				(DataStream& ds);		// #TODO
	bool	StoreState				(DataStream& ds) const;	// #TODO

private slots:
	void	ProtocolChanged			();
	void	ConnectionTypeChanged	();
	void	Connect					();
	void	Disconnect				();
	void	SetAsDefault			() const;

private:
	Owner<Ui::ConnectionWidgetClass>	ui;
	ConnectionSettings*					settings;

	using SettingsWidgets = HashTable<QString, Owner<ConnectionSettings>>;
	SettingsWidgets						settingsWidgets;

	Communication::Connection&			connection;
	Utilities::Logger&					logger;
};


#endif