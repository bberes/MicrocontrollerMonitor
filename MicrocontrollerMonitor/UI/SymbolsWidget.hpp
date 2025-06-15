#pragma once
#ifndef UI__SymbolsWidget__hpp
#define UI__SymbolsWidget__hpp

// #Kernel
#include "Types\Owner.hpp"
#include "KernelTypes.hpp"

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"
#include "ToggleableWidget.hpp"


class SymbolsWidget final : public ToggleableWidget {
	Q_OBJECT

public:
	explicit SymbolsWidget (Environment& environment, QWidget* parent = nullptr);
	~SymbolsWidget ();

	void			Load				(const QString& fileName);

private:
	void			Clear				();
	void			LoadFromFile		(const QString& fileName);
	bool			LoadFromCache		(const QString& fileName);
	bool			LoadFromCache		(DataStream& ds);
	bool			CacheEntries		(const QString& fileName) const;

private:
	virtual void	OnShowEvent			() override;

#ifndef QT_NO_CONTEXTMENU
	virtual void	contextMenuEvent	(QContextMenuEvent* event) override;
#endif

private slots:
	void			RefreshList			();
	void			AddSelectedToWatch	();

private:
	class  Data;
	struct Entry;

	Owner<Ui::SymbolsWidgetClass>	ui;
	Owner<Data>						data;

	WatchWindowTableModel&			wwTableModel;
};


#endif