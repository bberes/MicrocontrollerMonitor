#include "ProcessorTab.hpp"

// #QtUI
#include "ui_ProcessorTab.h"

// #Standard
#include <stdexcept>

// #Qt
#include <QTabBar>

// #MicrocontrollerMonitor
#include "MonitoringTab.hpp"


ProcessorTab::ProcessorTab (QWidget* parent/* = nullptr*/)
	: QWidget	(parent)
	, ui		(std::make_unique<Ui::ProcessorTabClass> ())
{
	ui->setupUi (this);

	QObject::connect (ui->tabWidget->tabBar (), SIGNAL (tabCloseRequested (int)), this, SLOT (CloseTab (int)));
}


ProcessorTab::~ProcessorTab ()
{
	for (auto& tab : tabs) {
		delete tab.second;
	}
}


void ProcessorTab::NewMonitoringTab (Int32 processorID, Int32 tabIndex)
{
	if (HasMonitoringTab (tabIndex)) {
		return;
	}

	NewMonitoringTabImpl (processorID, tabIndex);
}


bool ProcessorTab::HasMonitoringTab (Int32 tabIndex) const
{
	return tabs.count (tabIndex) != 0u;
}


MonitoringTab* ProcessorTab::GetMonitoringTab (Int32 tabIndex)
{
	if (!HasMonitoringTab (tabIndex)) {
		throw std::invalid_argument ("{DB981A18-4C50-4857-AB2E-E1FDB26488DF}");
	}

	return tabs.at (tabIndex);
}


void ProcessorTab::NewMonitoringTabImpl (Int32 processorID, Int32 tabIndex)
{
	auto tab = new MonitoringTab (processorID, tabIndex);
	tabs[tabIndex] = tab;
	ui->tabWidget->addTab (tab, QString::number (tabIndex));
}


void ProcessorTab::OpenTab (QWidget* tab)
{
	auto index = ui->tabWidget->indexOf (tab);
	ui->tabWidget->setTabVisible (index, true);
}


void ProcessorTab::CloseTab (int index)
{
	ui->tabWidget->setTabVisible (index, false);
}