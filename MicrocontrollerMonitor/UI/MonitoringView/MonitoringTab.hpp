#pragma once
#ifndef UI__MonitoringTab__hpp
#define UI__MonitoringTab__hpp

// #Qt
#include <QWidget>

// #Kernel
#include "Types\BaseTypes.hpp"
#include "Types\Owner.hpp"
#include "KernelTypes.hpp"

// #Communication
#include "CommunicationTypes.hpp"

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"


class MonitoringTab final : public QWidget {
	Q_OBJECT

public:
	explicit MonitoringTab (Utilities::Logger& logger, Int32 processorID, Int32 tabIndex, QWidget* parent = nullptr);
	~MonitoringTab ();

	void			SetProtocol		(Communication::Protocol& protocol);

public slots:
	void			ChangeRate		();
	void			AutoRefresh		(bool autoRefresh);
	void			RequestData		();
	void			RequestValues	();

private:
	virtual void	customEvent		(QEvent* event) override;

private:
	Owner<Ui::MonitoringTabClass>	ui;

	Int32							processorID;
	Int32							tabIndex;

	MonitoringTabTableModel*		tableModel;

	QTimer*							timer;

	Communication::Protocol*		protocol;
};


#endif