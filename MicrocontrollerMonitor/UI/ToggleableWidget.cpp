#include "ToggleableWidget.hpp"

// #MicrocontrollerMonitor
#include "Utilities.hpp"


ToggleableWidget::ToggleableWidget (QWidget* parent/* = nullptr*/)
	: QWidget	(parent)
	, action	(MakeChild<QAction> (*this))
{
	action->setObjectName ("action");
	action->setCheckable (true);
	connect (action, &QAction::toggled, this, &QWidget::setVisible);
}


ToggleableWidget::~ToggleableWidget () = default;


QAction* ToggleableWidget::toggleViewAction () const
{
	action->setText (windowTitle ());
	return action;
}


void ToggleableWidget::OnShowEvent ()
{
}


void ToggleableWidget::OnHideEvent ()
{
}


void ToggleableWidget::showEvent (QShowEvent* event)
{
	action->setChecked (true);
	QWidget::showEvent (event);
	OnShowEvent ();
}


void ToggleableWidget::hideEvent (QHideEvent* event)
{
	action->setChecked (false);
	QWidget::hideEvent (event);
	OnHideEvent ();
}