#pragma once
#ifndef UI__ProcessorView__hpp
#define UI__ProcessorView__hpp

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


class ProcessorView final : public QWidget {
	Q_OBJECT

public:
	ProcessorView (QWidget* parent = nullptr);
	~ProcessorView ();

	void			NewMonitoringTab	(Utilities::Logger& logger, Int32 processorID, Int32 tabIndex);
	bool			HasMonitoringTab	(Int32 processorID, Int32 tabIndex) const;
	MonitoringTab*	GetMonitoringTab	(Int32 processorID, Int32 tabIndex);

private:
	void			NewProcessorTabImpl	(Utilities::Logger& logger, Int32 processorID);
	bool			HasProcessorTab		(Int32 processorID) const;

private slots:
	void			OpenTab				(QWidget* tab);
	void			CloseTab			(int index);

private:
	Owner<Ui::ProcessorViewClass>	ui;

	using Tabs = std::unordered_map<Int32, ProcessorTab*>;
	Tabs							tabs;
};


#endif