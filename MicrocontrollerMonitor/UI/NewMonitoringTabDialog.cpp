#include "NewMonitoringTabDialog.hpp"

// #QtUI
#include "ui_NewMonitoringTabDialog.h"

// #Communication
#include "Protocols\HiTerm\CommandData\MonTabIndex.hpp"

// #MicrocontrollerMonitor
#include "Utilities.hpp"


NewMonitoringTabDialog::NewMonitoringTabDialog (QWidget* parent)
	: QDialog		(parent)
	, ui			(std::make_unique<Ui::NewMonitoringTabDialogClass> ())
	, intValidator	(MakeChild<QIntValidator> (*this))
{
	ui->setupUi (this);

	intValidator->setBottom (0);
	intValidator->setTop (127); // #TODO Use named constant variable/constexpr

	ui->lineEditProcessorID->setValidator (intValidator);

	Communication::HiTerm::EnumerateTabIndices ([this] (auto i) {
		auto v = static_cast<Int32> (i);
		ui->comboBoxTabIndex->addItem (QString::number (v), v);
	});
}


NewMonitoringTabDialog::~NewMonitoringTabDialog () = default;


Int32 NewMonitoringTabDialog::GetProcessorID () const
{
	return ui->lineEditProcessorID->text ().toInt ();
}


Int32 NewMonitoringTabDialog::GetTabIndex () const
{
	return ui->comboBoxTabIndex->currentData ().toInt ();
}