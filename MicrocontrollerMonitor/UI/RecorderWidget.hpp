#pragma once
#ifndef UI__RecorderWidget__hpp
#define UI__RecorderWidget__hpp

// #Kernel
#include "Types\Owner.hpp"

// #Communication
#include "CommunicationTypes.hpp"

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"
#include "ToggleableWidget.hpp"


class GraphWidget final : public QWidget {
public:
	explicit GraphWidget (QWidget* parent);

	void SetSamples (const Vector<UInt32>& values);

private:
	void paintEvent (QPaintEvent*) override;
	
private:
	Vector<float> samples;
};


class RecorderWidget final : public ToggleableWidget {
	Q_OBJECT

public:
	explicit RecorderWidget (Environment& env, QWidget* parent = nullptr);
	~RecorderWidget ();

private:
	virtual void	customEvent		(QEvent* event) override;

	void			ReadState		();
	void			WriteParams		();
	void			ReadParams		();
	void			ReadArray		();

private slots:
	void			StartRecording	();
	void			ProcessState	(bool ready);
	void			QueryParams		();
	void			CheckParams		();
	void			ProcessData		();

private:
	Owner<Ui::RecorderWidget>	ui;

	GraphWidget*				graph;

	Environment&				env;
	Communication::Connection&	connection;

	Owner<StateListener>		stateListener;
	Owner<WriteListener>		writeListener;
	Owner<ParamsListener>		paramsListener;
	Owner<ArrayListener>		arrayListener;
};


#endif