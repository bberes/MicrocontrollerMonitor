#pragma once
#ifndef Data__WatchWindowTableModel__hpp
#define Data__WatchWindowTableModel__hpp

// #Qt
#include <QAbstractTableModel>

// #Kernel
#include "Types\BaseTypes.hpp"
#include "KernelTypes.hpp"

// #Communication
#include "Data\WatchWindowTable.hpp"
#include "ResponseListeners.hpp"


class WatchWindowTableModel final
	: public QAbstractTableModel
	, public Communication::ReadVariablesResponseListener
{
	Q_OBJECT

public:
	explicit WatchWindowTableModel (QObject* parent = nullptr);

	void						AddVariable		(const QString& name, const QString& address, const QString& typeName);
	Communication::Variable		GetVariable		(const QModelIndex& index) const;

	Communication::MemoryRefs	GetMemoryRefs	() const;

	bool						LoadState		(DataStream& ds);		// #TODO
	bool						StoreState		(DataStream& ds) const;	// #TODO

private:
	virtual void				Update			(const Communication::Variables& variables) override;

	virtual bool				setData			(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	virtual Qt::ItemFlags		flags			(const QModelIndex& index) const override;
	virtual int					rowCount		(const QModelIndex& parent = QModelIndex ()) const override;
	virtual int					columnCount		(const QModelIndex& parent = QModelIndex ()) const override;
	virtual QVariant			data			(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual QVariant			headerData		(int section, Qt::Orientation orientation, int role) const override;

private:
	WatchWindow::Table table;
};


#endif