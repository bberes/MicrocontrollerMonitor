#include "MonitoringTabTableModel.hpp"

// #Communication
#include "Data\TabDataEntry.hpp"


MonitoringTabTableModel::MonitoringTabTableModel (QObject* parent)
	: QAbstractTableModel (parent)
{
}


void MonitoringTabTableModel::Update (const Communication::TabDataEntries& entries)
{
	// #ToDo: check tab index, response request mismatch error!
	if (mData.size () != 0u && mData.size () != entries.size ()) { // workaround, temporary
		return;
	}

	beginResetModel ();

	mData.clear ();
	for (auto& entry : entries) {
		Row row;
		row.resize (7);
		row[0] = QString::fromStdString (entry.name);
		row[1] = QString::fromStdString (entry.unit);
		row[2] = QString::number (entry.type, 16);
		row[3] = QString::number (entry.ptr, 16);
		row[4] = QString::number (entry.pMax);
		row[5] = QString::number (entry.pMin);
		mData.push_back (row);
	}

	endResetModel ();
}


void MonitoringTabTableModel::Update (const Communication::TabValues& values)
{
	// #ToDo: check tab index, response request mismatch error!
	if (mData.size () != values.size ()) { // workaround, temporary
		return;
	}

	for (size_t i = 0u; i < mData.size (); ++i) {
		auto& row = mData[i];
		row[6] = QString::number (values[i]);
	}

	if (mData.empty ()) {
		return;
	}

	emit dataChanged (index (0, 6), index (static_cast<int> (mData.size ()) - 1, 6), { Qt::DisplayRole });
}


int MonitoringTabTableModel::rowCount (const QModelIndex& /*parent*/) const
{
	return static_cast<int> (mData.size ());
}


int MonitoringTabTableModel::columnCount (const QModelIndex& /*parent*/) const
{
	if (mData.empty ()) {
		return 0;
	}
	return static_cast<int> (mData.front ().size ());
}


QVariant MonitoringTabTableModel::data (const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		return mData[index.row ()][index.column ()];
	}

	return QVariant ();
}


QVariant MonitoringTabTableModel::headerData (int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section) {
		case 0: return QString ("Name");
		case 1: return QString ("Unit");
		case 2: return QString ("Type");
		case 3: return QString ("Address");
		case 4: return QString ("pMin");
		case 5: return QString ("pMax");
		case 6: return QString ("Value");
		}
	}

	return QVariant ();
}