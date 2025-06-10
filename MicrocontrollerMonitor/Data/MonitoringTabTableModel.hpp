#pragma once
#ifndef Data__MonitoringTabTableModel__hpp
#define Data__MonitoringTabTableModel__hpp

// #Qt
#include <QAbstractTableModel>

// #Communication
#include "ResponseListeners.hpp"


class MonitoringTabTableModel final
	: public QAbstractTableModel
	, public Communication::TabDataResponseListener
	, public Communication::TabValuesResponseListener
{
	Q_OBJECT

public:
	MonitoringTabTableModel (QObject* parent = nullptr);

private:
	virtual void		Update		(const Communication::TabDataEntries& entries) override;
	virtual void		Update		(const Communication::TabValues& values) override;

private:
	virtual int			rowCount	(const QModelIndex& parent = QModelIndex ()) const override;
	virtual int			columnCount	(const QModelIndex& parent = QModelIndex ()) const override;
	virtual QVariant	data		(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual QVariant	headerData	(int section, Qt::Orientation orientation, int role) const override;

private:
	using Row	= std::vector<QString>;
	using Data	= std::vector<Row>;

	Data mData;
};


#endif