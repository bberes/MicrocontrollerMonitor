#pragma once
#ifndef UI__WatchWindowWidget__hpp
#define UI__WatchWindowWidget__hpp

// #Kernel
#include "Types\Owner.hpp"
#include "KernelTypes.hpp"

// #Communication
#include "CommunicationTypes.hpp"

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"
#include "ToggleableWidget.hpp"


class WatchWindowWidget final : public ToggleableWidget {
	Q_OBJECT

public:
	explicit WatchWindowWidget (Utilities::Logger& logger, QWidget* parent = nullptr);
	~WatchWindowWidget ();

	void			SetProtocol		(Communication::Protocol& protocol);
	void			AddVariable		(const QString& name, const QString& address, const QString& typeName);

private slots:
	void			ChangeRate		();
	void			AutoRefresh		(bool autoRefresh);
	void			RequestValues	();
	void			HandleChange	(const QModelIndex& topLeft, const QModelIndex& bottomRight);

private:
	void			RequestWrite	(const Communication::Variable& variable);
	virtual void	customEvent		(QEvent* event) override;

private:
	Owner<Ui::WatchWindowWidgetClass>	ui;

	WatchWindowTableModel*				tableModel;

	QTimer*								timer;

	Communication::Protocol*			protocol;
};


#endif