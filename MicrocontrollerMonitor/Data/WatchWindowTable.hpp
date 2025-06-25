#pragma once
#ifndef Data__WatchWindow_Table__hpp
#define Data__WatchWindow_Table__hpp

// #Qt
#include <QString>

// #Kernel
#include "KernelTypes.hpp"

// #Communication
#include "CommunicationTypes.hpp"

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"


namespace WatchWindow {

class Row final {
public:
	Row () = default;
	explicit Row (const QString& name, const QString& address, const QString& typeName);

	void						SetValue	(const Communication::Variable& variable);
	void						SetValue	(const QString& v);

	void						Load		(DataStream& ds);
	void						Store		(DataStream& ds) const;

	Communication::Variable		ToVariable	() const;
	Communication::MemoryRef	ToMemoryRef	() const;
	const QString&				operator[]	(int index) const;

	constexpr static int		MemberCount	() { return 4; } // name, address, typeName, value

private:
	QString name;
	QString address;
	QString typeName;
	QString value;
};


class Table final {
public:
	void						SetValue		(const size_t i, const Communication::Variable& variable);
	bool						SetData			(const QModelIndex& index, const QVariant& value);
	bool						SetData			(size_t i, const QString& value);
	void						AddRow			(const QString& name, const QString& address, const QString& typeName);

	void						Load			(DataStream& ds);
	void						Store			(DataStream& ds) const;

	Communication::Variables	ToVariables		() const;
	Communication::MemoryRefs	ToMemoryRefs	() const;
	const Row&					operator[]		(int index) const;
	bool						IsEditable		(const QModelIndex& index) const;

	int							RowCount		() const { return static_cast<int> (rows.size ()); } // #ToDo: add assertion
	int							ColumnCount		() const { return Row::MemberCount (); }

private:
	Vector<Row> rows;
};

}


#endif