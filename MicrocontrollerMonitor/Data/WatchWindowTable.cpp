#include "WatchWindowTable.hpp"

// #Qt
#include <QModelIndex>
#include <QVariant>

// #Kernel
#include "Types\DataStream.hpp"
#include "Types\Owner.hpp"
#include "Utilities\Debug.hpp"
#include "Utilities\Variable.hpp"

// #Communication
#include "Data\Variable.hpp"

// #FileHandler
#include "FileFormats\COFF\SymbolTable\TypeDescriptor.hpp"


WatchWindow::Row::Row (const QString& name, const QString& address, const QString& typeName)
	: name		(name)
	, address	(address)
	, typeName	(typeName)
{
}


namespace {

bool IsPointer (const QString& typeName)
{
	return !typeName.isEmpty () && typeName[0u] == '*';
}


bool IsBitField (const QString& typeName)
{
	return typeName.length () > 1u && typeName[0u] == 'B';
}


Owner<Utilities::IVariable> ToIVariable (const Communication::Variable& variable, const QString& typeName)
{
	if (IsPointer (typeName)) {
		return std::make_unique<Utilities::Variable<UInt32>> (variable.GetValue<UInt32> ());
	}

	if (typeName == File::COFF::TextChar) {
		return std::make_unique<Utilities::Variable<Int8>> (variable.GetValue<Int8> ());
	}
	if (typeName == File::COFF::TextUChar) {
		return std::make_unique<Utilities::Variable<UInt8>> (variable.GetValue<UInt8> ());
	}
	if (typeName == File::COFF::TextInt16) {
		return std::make_unique<Utilities::Variable<Int16>> (variable.GetValue<Int16> ());
	}
	if (typeName == File::COFF::TextUInt16 || IsBitField (typeName) && typeName[1u] == '1') {
		return std::make_unique<Utilities::Variable<UInt16>> (variable.GetValue<UInt16> ());
	}
	if (typeName == File::COFF::TextInt32) {
		return std::make_unique<Utilities::Variable<Int32>> (variable.GetValue<Int32> ());
	}
	if (typeName == File::COFF::TextUInt32 || IsBitField (typeName) && typeName[1u] == '3') {
		return std::make_unique<Utilities::Variable<UInt32>> (variable.GetValue<UInt32> ());
	}
	if (typeName == File::COFF::TextFloat) {
		return std::make_unique<Utilities::Variable<float>> (variable.GetValue<float> ());
	}

	TODO; // #ToDo: Check these types below! (source: fn. File::COFF::ToString) 
	// Void, UNKNOWN, Int16, Double, Struct, Union, Enum, MemberOfEnum, UInt16
}


QString ToString (const Communication::Variable& variable, const QString& typeName)
{
	auto v = ToIVariable (variable, typeName);
	const bool isHEX = IsPointer (typeName) || IsBitField (typeName); // #ToDo: BitField MASK
	std::string s = isHEX ? v->ToHEX (Utilities::ToHexModifier::KeepZeros) : v->ToString ();
	return QString::fromStdString (s);
}

}


void WatchWindow::Row::SetValue (const Communication::Variable& variable)
{
	value = ToString (variable, typeName);
}


void WatchWindow::Row::SetValue (const QString& v)
{
	value = v;
}


void WatchWindow::Row::Load (DataStream& ds)
{
	ds >> name >> address >> typeName;
}


void WatchWindow::Row::Store (DataStream& ds) const
{
	ds << name << address << typeName;
}


static UInt32 ToUInt32 (const QString& value)
{
	bool ok = false;
	UInt32 v = value.toUInt (&ok);
	if (ok) {
		return v;
	}

	v = value.toUInt (&ok, 16);
	if (ok) {
		return v;
	}

	TODO;
}


Communication::Variable WatchWindow::Row::ToVariable () const
{
	bool ok = false;
	UInt32 addr = address.toUInt (&ok, 16);
	if (!ok) {
		TODO;
	}

	if (typeName == File::COFF::TextFloat) {
		float v = value.toFloat ();
		UInt32 r;
		std::memcpy (&r, &v, sizeof (float));
		return Communication::Variable (r, addr);
	}
	if (typeName == File::COFF::TextChar || typeName == File::COFF::TextUChar) {
		return Communication::Variable (static_cast<UInt8> (ToUInt32 (value)), addr);
	}
	if (typeName == File::COFF::TextInt16 || typeName == File::COFF::TextUInt16) {
		return Communication::Variable (static_cast<UInt16> (ToUInt32 (value)), addr);
	}
	if (typeName == File::COFF::TextInt32 || typeName == File::COFF::TextUInt32 || IsPointer (typeName)) {
		return Communication::Variable (static_cast<UInt32> (ToUInt32 (value)), addr);
	}

	TODO; // #ToDo: BitField?
}


namespace {

Communication::VariableSize ToSize (const QString& typeName)
{
	if (IsPointer (typeName)) {
		return Communication::VariableSize::Size4Bytes;
	}

	if (IsBitField (typeName)) {
		if (typeName[1u] == '1') { // B16
			return Communication::VariableSize::Size2Bytes;
		}
		if (typeName[1u] == '3') { // B32
			return Communication::VariableSize::Size4Bytes;
		}
	}

	if (typeName == File::COFF::TextChar || typeName == File::COFF::TextUChar) {
		return Communication::VariableSize::Size1Byte;
	}

	if (typeName == File::COFF::TextInt16 || typeName == File::COFF::TextUInt16) {
		return Communication::VariableSize::Size2Bytes;
	}

	if (typeName == File::COFF::TextInt32 || typeName == File::COFF::TextUInt32 || typeName == File::COFF::TextFloat) {
		return Communication::VariableSize::Size4Bytes;
	}

	TODO; // #ToDo: Check these types below! (source: fn. File::COFF::ToString) 
	// Void, UNKNOWN, Int16, Double, Struct, Union, Enum, MemberOfEnum, UInt16
}

}


Communication::MemoryRef WatchWindow::Row::ToMemoryRef () const
{
	constexpr size_t StringLength = 1u + 1u + 8u; // e.g. 0x12345678
	if (address.length () != StringLength || address[0] != '0' || address[1] != 'x') {
		TODO; // #ToDo
	}
	bool converted = false;
	const UInt32 addr = address.toUInt (&converted, 16);
	if (!converted) {
		TODO; // #ToDo
	}
	return Communication::MemoryRef (addr, ToSize (typeName));
}


const QString& WatchWindow::Row::operator[] (int index) const
{
	switch (index) {
	case 0: return name;
	case 1: return address;
	case 2: return typeName;
	case 3: return value;
	default:
		TODO; // #ToDo: invalid state
	}
}


void WatchWindow::Table::SetValue (const size_t i, const Communication::Variable& variable)
{
	rows[i].SetValue (variable);
}


bool WatchWindow::Table::SetData (const QModelIndex& index, const QVariant& value)
{
	if (!IsEditable (index)) {
		TODO;
	}
	
	return SetData (index.row (), value.toString ());
}


bool WatchWindow::Table::SetData (size_t i, const QString& value)
{
	bool ok = false;
	value.toDouble (&ok);
	if (!ok) {
		value.toInt (&ok, 16);
		if (!ok) {
			return false;
		}
	}

	rows[i].SetValue (value);

	return true;
}


void WatchWindow::Table::AddRow (const QString& name, const QString& address, const QString& typeName)
{
	rows.push_back (Row (name, address, typeName));
}


void WatchWindow::Table::Load (DataStream& ds)
{
	size_t n = 0u;
	ds >> n;

	for (size_t i = 0u; i < n; ++i) {
		Row row;
		row.Load (ds);
		rows.push_back (row);
	}
}


void WatchWindow::Table::Store (DataStream& ds) const
{
	ds << rows.size ();

	for (const Row& row : rows) {
		row.Store (ds);
	}
}


Communication::Variables WatchWindow::Table::ToVariables () const
{
	Communication::Variables variables;
	for (const Row& row : rows) {
		variables.push_back (row.ToVariable ());
	}
	return variables;
}


Communication::MemoryRefs WatchWindow::Table::ToMemoryRefs () const
{
	Communication::MemoryRefs memoryRefs;
	for (const Row& row : rows) {
		memoryRefs.push_back (row.ToMemoryRef ());
	}
	return memoryRefs;
}


const WatchWindow::Row& WatchWindow::Table::operator[] (int index) const
{
	return rows[index];
}


bool WatchWindow::Table::IsEditable (const QModelIndex& index) const
{
	return index.column () == 3;
}