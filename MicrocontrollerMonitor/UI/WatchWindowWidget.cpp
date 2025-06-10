#include "WatchWindowWidget.hpp"

// #QtUI
#include "ui_WatchWindowWidget.h"

// #Qt
#include <QFile>
#include <QStyledItemDelegate>
#include <QTimer>

// #Kernel
#include "Utilities\Debug.hpp"

// #Communication
#include "Requests\ReadVariablesRequest.hpp"
#include "Requests\WriteVariablesRequest.hpp"
#include "CommunicationProtocol.hpp"

// #MicrocontrollerMonitor
#include "Data\WatchWindowTableModel.hpp"
#include "CustomEvent.hpp"


static const QString configFileName (".RuntimeCache\\WatchWindowVariables.cfg");


class DelegateWithRefreshSuspension : public QStyledItemDelegate {
public:
	explicit DelegateWithRefreshSuspension (QCheckBox& cb, QObject* parent = nullptr)
		: QStyledItemDelegate	(parent)
		, checkBox				(cb)
		, wasChecked			(false)
	{
	}

private:
	virtual QWidget* createEditor (QWidget* p, const QStyleOptionViewItem& o, const QModelIndex& i) const override
	{
		wasChecked = checkBox.isChecked (); // #ToDo: auto refresh suspension
		checkBox.setChecked (false);
		return QStyledItemDelegate::createEditor (p, o, i);
	}

//	virtual void setModelData (QWidget* editor, QAbstractItemModel* m, const QModelIndex& i) const override
//	{
//		QStyledItemDelegate::setModelData (editor, m, i);
//	}

	virtual void destroyEditor (QWidget* editor, const QModelIndex& i) const override
	{
		checkBox.setChecked (wasChecked);
		QStyledItemDelegate::destroyEditor (editor, i);
	}

private:
	QCheckBox&		checkBox;
	mutable bool	wasChecked;
};


WatchWindowWidget::WatchWindowWidget (Utilities::Logger& logger, QWidget* parent)
	: ToggleableWidget	(parent)
	, ui				(std::make_unique<Ui::WatchWindowWidgetClass> ())
	, tableModel		(new WatchWindowTableModel)
	, timer				(new QTimer (this))
	, protocol			(nullptr)
{
	ui->setupUi (this);

	ui->tableView->setModel (tableModel);
	ui->tableView->setItemDelegate (new DelegateWithRefreshSuspension (*ui->checkBox, ui->tableView));
	ui->tableView->setEditTriggers (QAbstractItemView::AllEditTriggers);

	AutoRefresh (false);
	connect (ui->spinBox   , &QSpinBox::valueChanged         , this, &WatchWindowWidget::ChangeRate   );
	connect (ui->checkBox  , &QCheckBox::toggled             , this, &WatchWindowWidget::AutoRefresh  );
	connect (ui->pushButton, &QPushButton::pressed           , this, &WatchWindowWidget::RequestValues);
	connect (timer         , &QTimer::timeout                , this, &WatchWindowWidget::RequestValues);
	connect (tableModel    , &QAbstractItemModel::dataChanged, this, &WatchWindowWidget::HandleChange );

	// #TODO It should be elsewhere!
	QFile config (configFileName);
	if (config.open (QIODevice::ReadOnly)) {
		DataStream ds (&config);
		tableModel->LoadState (ds);
	}
}


WatchWindowWidget::~WatchWindowWidget ()
{
	// #TODO ?
	QFile config (configFileName);
	if (config.open (QIODevice::WriteOnly)) {
		DataStream ds (&config);
		tableModel->StoreState (ds);
	}

	delete tableModel;
}


void WatchWindowWidget::SetProtocol (Communication::Protocol& protocol)
{
	this->protocol = &protocol;
}


void WatchWindowWidget::AddVariable (const QString& name, const QString& address, const QString& typeName)
{
	tableModel->AddVariable (name, address, typeName);
}


void WatchWindowWidget::ChangeRate ()
{
	AutoRefresh (true);
}


void WatchWindowWidget::AutoRefresh (bool autoRefresh)
{
	if (autoRefresh) {
		ui->pushButton->setEnabled (false);
		ui->spinBox   ->setEnabled (true );
		timer->setInterval (ui->spinBox->value ());
		timer->start ();
	} else {
		ui->pushButton->setEnabled (true );
		ui->spinBox   ->setEnabled (false);
		timer->stop ();
	}
}


void WatchWindowWidget::RequestValues ()
{
	protocol->AddListener (*tableModel);
	QCoreApplication::postEvent (this, new CustomEvent ([this] () {
		constexpr UInt8 processorID = 0u;
		const auto& memoryRefs = tableModel->GetMemoryRefs ();
		const Communication::ReadVariablesRequest valuesRequest (processorID, memoryRefs);
		protocol->SendRequest (valuesRequest);
	}));
}


void WatchWindowWidget::HandleChange (const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
	if (topLeft != bottomRight || topLeft.column () != 3) {
		TODO; // #ToDo
	}

	RequestWrite (tableModel->GetVariable (topLeft));
}


void WatchWindowWidget::RequestWrite (const Communication::Variable& variable)
{
	QCoreApplication::postEvent (this, new CustomEvent ([this, variable] () {
		constexpr UInt8 processorID = 0u;
		const Communication::WriteVariablesRequest writeRequest (processorID, { variable });
		protocol->SendRequest (writeRequest);
	}));
}


void WatchWindowWidget::customEvent (QEvent* event)
{
	static_cast<CustomEvent*> (event)->Process ();
}