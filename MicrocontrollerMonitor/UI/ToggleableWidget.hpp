#pragma once
#ifndef UI__ToggleableWidget__hpp
#define UI__ToggleableWidget__hpp

// #Qt
#include <QWidget>


class ToggleableWidget : public QWidget {
	Q_OBJECT

public:
	ToggleableWidget (QWidget* parent = nullptr);
	~ToggleableWidget ();

	QAction*		toggleViewAction	() const;

private:
	virtual void	OnShowEvent			();
	virtual void	OnHideEvent			();

private:
	virtual void	showEvent			(QShowEvent* event) override final;
	virtual void	hideEvent			(QHideEvent* event) override final;

private:
	QAction* action;
};


#endif