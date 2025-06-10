#include "WatchWindowTableModel.hpp"

// #Kernel
#include "Types\DataStream.hpp"
#include "Utilities\Debug.hpp"

// #Communication
#include "Data\Variable.hpp"


WatchWindowTableModel::WatchWindowTableModel (QObject* parent)
	: QAbstractTableModel (parent)
{
}


void WatchWindowTableModel::AddVariable (const QString& name, const QString& address, const QString& typeName)
{
	beginResetModel ();
	table.AddRow (name, address, typeName);
	endResetModel ();
}


static const QString GUID ("{12C1DA00-0418-4BD5-AF68-32FFB4E85A8E}");


bool WatchWindowTableModel::LoadState (DataStream& ds)
{
	QString guid;
	ds >> guid;
	if (GUID != guid) {
		return false;
	}

	beginResetModel ();
	table.Load (ds);
	endResetModel ();

	return ds.status () == DataStream::Status::Ok;
}


bool WatchWindowTableModel::StoreState (DataStream& ds) const
{
	ds << GUID;

	table.Store (ds);

	return ds.status () == DataStream::Status::Ok;
}


Communication::Variable WatchWindowTableModel::GetVariable (const QModelIndex& index) const
{
	if (index.column () != 3) {
		TODO; // #ToDo illegal state
	}

	return table[index.row ()].ToVariable ();
}


Communication::MemoryRefs WatchWindowTableModel::GetMemoryRefs () const
{
	return table.ToMemoryRefs ();
}


void WatchWindowTableModel::Update (const Communication::Variables& variables)
{
	const auto& memoryRefs = GetMemoryRefs ();
	if (memoryRefs.size () != variables.size ()) {
		TODO; // #ToDo
	}

	beginResetModel (); // #ToDo: Use scope variable (guard)!

	for (size_t i = 0u; i < variables.size (); ++i) {
		if (memoryRefs[i] != variables[i].GetInfo ()) {
			TODO; // #ToDo
		}
		table.SetValue (i, variables[i]);
	}

	endResetModel ();
}


bool WatchWindowTableModel::setData (const QModelIndex& index, const QVariant& value, int role/* = Qt::EditRole*/)
{
	if (role != Qt::EditRole) {
		return false;
	}

	if (!table.SetData (index, value)) {
		return false;
	}

	emit dataChanged (index, index);

	return true;
}


Qt::ItemFlags WatchWindowTableModel::flags (const QModelIndex& index) const
{
	if (table.IsEditable (index)) {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}

	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}


int WatchWindowTableModel::rowCount (const QModelIndex& /*parent*/) const
{
	return table.RowCount ();
}


int WatchWindowTableModel::columnCount (const QModelIndex& /*parent*/) const
{
	return table.ColumnCount ();
}


QVariant WatchWindowTableModel::data (const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		return table[index.row ()][index.column ()];
	}

	return QVariant ();
}


QVariant WatchWindowTableModel::headerData (int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section) {
		case 0: return QString ("Name");
		case 1: return QString ("Address");
		case 2: return QString ("Type");
		case 3: return QString ("Value");
		}
	}

	return QVariant ();
}