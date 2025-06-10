#pragma once
#ifndef UI__ProcessorTab__hpp
#define UI__ProcessorTab__hpp

// #Standard
#include <unordered_map>

// #Qt
#include <QWidget>

// #Kernel
#include "Types\BaseTypes.hpp"
#include "Types\Owner.hpp"
#include "KernelTypes.hpp"

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"


class ProcessorTab final : public QWidget {
	Q_OBJECT

public:
	explicit ProcessorTab (Utilities::Logger& logger, QWidget* parent = nullptr);
	~ProcessorTab ();

	void			NewMonitoringTab		(Int32 processorID, Int32 tabIndex);
	bool			HasMonitoringTab		(Int32 tabIndex) const;
	MonitoringTab*	GetMonitoringTab		(Int32 tabIndex);

private:
	void			NewMonitoringTabImpl	(Int32 processorID, Int32 tabIndex);

private slots:
	void			OpenTab					(QWidget* tab);
	void			CloseTab				(int index);

private:
	Owner<Ui::ProcessorTabClass>	ui;

	using Tabs = std::unordered_map<Int32, MonitoringTab*>;
	Tabs							tabs;

	Utilities::Logger&				logger;
};


#endif