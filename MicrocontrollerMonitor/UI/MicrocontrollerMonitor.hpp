#pragma once
#ifndef UI__MicrocontrollerMonitor__hpp
#define UI__MicrocontrollerMonitor__hpp

// #Qt
#include <QtWidgets\QMainWindow>

// #Kernel
#include "Types\Owner.hpp"

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"


class MicrocontrollerMonitor final : public QMainWindow {
	Q_OBJECT

public:
	explicit MicrocontrollerMonitor (LogData& logData, QWidget* parent = nullptr);
	~MicrocontrollerMonitor ();

private:
	void			SetUpMenuView		();

	virtual void	customEvent			(QEvent* event) override;

private slots:
	void			NewMonitoringTab	();
	void			OpenSymbolFile		();

private:
	Owner<Ui::MicrocontrollerMonitorClass>	ui;

	Owner<Environment>						environment;

	Owner<QWidget>							connectionWidget;
	Owner<LoggerWidget>						loggerWidget;
	ProcessorView*							processorView;
	Owner<WatchWindowWidget>				watchWindow;
	Owner<SymbolsWidget>					symbolsWidget;
	Owner<RecorderWidget>					recorderWidget;
};


#endif