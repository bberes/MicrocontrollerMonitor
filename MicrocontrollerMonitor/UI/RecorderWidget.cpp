#include "RecorderWidget.hpp"

// #QtUI
#include "ui_RecorderWidget.h"

// #Qt
#include <QPainter>

// #Kernel
#include "Utilities\Debug.hpp"

// #Communication
#include "Requests\ReadArrayRequest.hpp"
#include "Requests\ReadVariablesRequest.hpp"
#include "Requests\WriteVariablesRequest.hpp"
#include "CommunicationProtocol.hpp"
#include "Connection.hpp"

// #MicrocontrollerMonitor
#include "Data\Environment.hpp"
#include "Data\RecorderTypes.hpp"
#include "Data\WatchWindowTable.hpp"
#include "CustomEvent.hpp"
#include "Utilities.hpp"


GraphWidget::GraphWidget (QWidget* parent)
	: QWidget (parent)
{
}


void GraphWidget::SetSamples (const std::vector<UInt32>& values)
{
	samples.resize (values.size () / 4);
	for (size_t i = 0u; i < values.size (); i += 4u) {
		static_assert (sizeof (UInt32) == sizeof (float));
		std::memcpy (&samples[i / 4u], &values[i], sizeof (UInt32));
	}
}


void GraphWidget::paintEvent (QPaintEvent*)
{
	if (samples.empty ()) {
		return;
	}

	QPainter painter (this);
	painter.setRenderHint (QPainter::Antialiasing);
	painter.fillRect (rect (), Qt::lightGray);
	painter.setPen (QPen (Qt::green, 2));

	const float w = width ();
	const float h = height ();

	const float dw = w / samples.size ();
	const float mh = h / 2;

	for (size_t j = 1; j < samples.size (); ++j) {
		const size_t i = j - 1;
		const int x1 = dw * j;
		const int x2 = x1 + dw;
		const int y1 = mh * (1 + samples[i]);
		const int y2 = mh * (1 + samples[j]);
		painter.drawLine (x1, y1, x2, y2);
	}
}


static Communication::MemoryRef GetRecorderStateMemRef (const WatchWindow::Table& table)
{
	for (int i = 0; table.RowCount (); ++i) {
		if (table[i][0] == "MUCI_RecorderParameter.state") {
			return table[i].ToMemoryRef ();
		}
	}
	TODO; // #ToDo: missing
}


RecorderWidget::RecorderWidget (Environment& env, QWidget* parent/* = nullptr*/)
	: ToggleableWidget	(parent)
	, ui				(std::make_unique<Ui::RecorderWidget> ())
	, graph				(MakeChild<GraphWidget> (*this))
	, env				(env)
	, connection		(env.GetConnection ())
	, stateListener		(std::make_unique<StateListener>  (GetRecorderStateMemRef (env.RecorderParams ())))
	, writeListener		(std::make_unique<WriteListener>  ())
	, paramsListener	(std::make_unique<ParamsListener> ())
	, arrayListener		(std::make_unique<ArrayListener>  ())
{
	ui->setupUi (this);

	ui->hLayoutTop->removeWidget (ui->widget);
	ui->hLayoutTop->insertWidget (0, graph);
	graph->setMinimumSize (640, 480);

	connect (ui->pButtonStart, &QPushButton::pressed, this, &RecorderWidget::StartRecording);

	connect (stateListener .get (), &StateListener::StateReceived  , this, &RecorderWidget::ProcessState);
	connect (writeListener .get (), &WriteListener::WriteFinished  , this, &RecorderWidget::QueryParams );
	connect (paramsListener.get (), &ParamsListener::ParamsReceived, this, &RecorderWidget::CheckParams );
	connect (arrayListener .get (), &ArrayListener::DataReceived   , this, &RecorderWidget::ProcessData );
}


RecorderWidget::~RecorderWidget () = default;


void RecorderWidget::customEvent (QEvent* event)
{
	static_cast<CustomEvent*> (event)->Process ();
}


void RecorderWidget::ReadState ()
{
	connection.GetProtocol ().AddListener (*stateListener);
	QCoreApplication::postEvent (this, MakeEvent<CustomEvent> ([this] () {
		constexpr UInt8 processorID = 0u;
		Communication::ReadVariablesRequest valuesRequest (processorID, { stateListener->mr });
		connection.GetProtocol ().SendRequest (valuesRequest);
	}));
}


void RecorderWidget::WriteParams ()
{
	connection.GetProtocol ().AddListener (*writeListener);
	QCoreApplication::postEvent (this, MakeEvent<CustomEvent> ([this] () {
		constexpr UInt8 processorID = 0u;
		Communication::Variables variables = env.RecorderParams ().ToVariables ();
		Communication::WriteVariablesRequest request (processorID, variables);
		connection.GetProtocol ().SendRequest (request);
	}));
}


void RecorderWidget::ReadParams ()
{
	connection.GetProtocol ().AddListener (*paramsListener);
	QCoreApplication::postEvent (this, MakeEvent<CustomEvent> ([this] () {
		constexpr UInt8 processorID = 0u;
		paramsListener->refs = env.RecorderParams ().ToMemoryRefs ();
		Communication::ReadVariablesRequest request (processorID, paramsListener->refs);
		connection.GetProtocol ().SendRequest (request);
	}));
}


void RecorderWidget::ReadArray ()
{
	connection.GetProtocol ().AddListener (*arrayListener);
	QCoreApplication::postEvent (this, MakeEvent<CustomEvent> ([this] () {
		constexpr UInt8 processorID = 0u;
		const UInt32 address = arrayListener->addr;
		const UInt16 length  = arrayListener->len;
		const Communication::ReadArrayRequest request (processorID, address, length);
		connection.GetProtocol ().SendRequest (request);
	}));
}


void RecorderWidget::StartRecording ()
{
	ReadState ();
}


void RecorderWidget::ProcessState (bool ready)
{
	if (ready) {
		WriteParams ();
	} else {
		ReadState ();
	}
}


void RecorderWidget::QueryParams ()
{
	ReadParams ();
}


void RecorderWidget::CheckParams ()
{
	// #ToDo: perform check and read data on success

	arrayListener->Init ();

	ReadArray ();
}


void RecorderWidget::ProcessData ()
{
	if (arrayListener->iter == 5u) {
		graph->SetSamples (arrayListener->data);
		return; // #ToDo: plot data
	}

	arrayListener->addr += ArrayListener::LengthUnit;
	if (arrayListener->iter == 4u) {
		arrayListener->len = ArrayListener::LengthLast;
	}

	ReadArray ();
}