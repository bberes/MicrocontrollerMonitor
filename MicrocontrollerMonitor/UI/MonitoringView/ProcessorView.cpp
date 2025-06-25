#include "ProcessorView.hpp"

// #QtUI
#include "ui_ProcessorView.h"

// #Standard
#include <stdexcept>

// #Qt
#include <QTabBar>

// #MicrocontrollerMonitor
#include "ProcessorTab.hpp"
#include "Utilities.hpp"


ProcessorView::ProcessorView (QWidget* parent/* = nullptr*/)
	: QWidget	(parent)
	, ui		(std::make_unique<Ui::ProcessorViewClass> ())
{
	ui->setupUi (this);

	QObject::connect (ui->tabWidget->tabBar (), SIGNAL (tabCloseRequested (int)), this, SLOT (CloseTab (int)));
}


ProcessorView::~ProcessorView () = default;


void ProcessorView::NewMonitoringTab (Int32 processorID, Int32 tabIndex)
{
	if (HasMonitoringTab (processorID, tabIndex)) {
		return;
	}

	if (!HasProcessorTab (processorID)) {
		NewProcessorTabImpl (processorID);
	}

	tabs.at (processorID)->NewMonitoringTab (processorID, tabIndex);
}


bool ProcessorView::HasMonitoringTab (Int32 processorID, Int32 tabIndex) const
{
	if (!HasProcessorTab (processorID)) {
		return false;
	}

	return tabs.at (processorID)->HasMonitoringTab (tabIndex);
}


MonitoringTab* ProcessorView::GetMonitoringTab (Int32 processorID, Int32 tabIndex)
{
	if (!HasProcessorTab (processorID)) {
		throw std::invalid_argument ("{F7552DDD-D6CA-4742-B2A5-0578C2AC9FDF}");
	}

	return tabs.at (processorID)->GetMonitoringTab (tabIndex);
}


void ProcessorView::NewProcessorTabImpl (Int32 processorID)
{
	auto tab = MakeChild<ProcessorTab> (*ui->tabWidget);
	tabs[processorID] = tab;
	ui->tabWidget->addTab (tab, QString::number (processorID));
}


bool ProcessorView::HasProcessorTab (Int32 processorID) const
{
	return tabs.count (processorID) != 0u;
}


void ProcessorView::OpenTab (QWidget* tab)
{
	auto index = ui->tabWidget->indexOf (tab);
	ui->tabWidget->setTabVisible (index, true);
}


void ProcessorView::CloseTab (int index)
{
	ui->tabWidget->setTabVisible (index, false);
}