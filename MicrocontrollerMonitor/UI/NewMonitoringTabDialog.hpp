#pragma once
#ifndef UI__NewMonitoringTabDialog__hpp
#define UI__NewMonitoringTabDialog__hpp

// #Qt
#include <QDialog>

// #Kernel
#include "Types\BaseTypes.hpp"
#include "Types\Owner.hpp"

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"


class NewMonitoringTabDialog final : public QDialog {
	Q_OBJECT

public:
	NewMonitoringTabDialog (QWidget* parent = nullptr);
	~NewMonitoringTabDialog ();

	Int32	GetProcessorID	() const;
	Int32	GetTabIndex		() const;

private:
	Owner<Ui::NewMonitoringTabDialogClass>	ui;
	QIntValidator*							intValidator;
};


#endif