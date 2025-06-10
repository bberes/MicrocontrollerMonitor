#include "MonTab.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"


Communication::HiTerm::MonTab::Entry::Entry (DeserializationSelector ds)
	: Deserializable (ds)
{
}


Communication::HiTerm::MonTab::Entry::Entry (Name name, Unit unit, Type type, Ptr ptr, PMax pMax, PMin pMin)
	: Deserializable	(RegularConstructor)
	, name				(name)
	, unit				(unit)
	, type				(type)
	, ptr				(ptr)
	, pMax				(pMax)
	, pMin				(pMin)
{
}


namespace {

size_t ReadCDAB (DataStream& ds, UInt32& data)
{
	size_t size = 0u;

	UInt16 low	= 0u;
	UInt16 high	= 0u;

	size += ::Read (ds, low, ByteOrder::MSBFirst);
	size += ::Read (ds, high, ByteOrder::MSBFirst);

	data = high;
	data <<= 16;
	data |= low;

	return size;
}


size_t WriteCDAB (DataStream& ds, const UInt32& data)
{
	size_t size = 0u;

	const UInt16 low	= data & 0xFFFF;
	const UInt16 high	= data >> 16;

	size += ::Write (ds, low, ByteOrder::MSBFirst);
	size += ::Write (ds, high, ByteOrder::MSBFirst);

	return size;
}

}


size_t Communication::HiTerm::MonTab::Entry::Read (DataStream& is)
{
	size_t size = 0u;
	bool eos = false;

	name.clear ();
	for (size_t i = 0u; i < NameFieldLength; ++i) {
		UInt16 data = 0u;
		size += ::Read (is, data, ByteOrder::MSBFirst);
		if (0u == data) {
			eos = true;
			continue;
		}
		if (eos) {
			TODO; // #TODO (inconsistent string)
		}
		name += static_cast<UInt8> (data);
	}

	size += ::Read (is, unit, ByteOrder::MSBFirst);
	size += ::Read (is, type, ByteOrder::MSBFirst);

	size += ::ReadCDAB (is, ptr);
	size += ::ReadCDAB (is, pMax);
	size += ::ReadCDAB (is, pMin);

	return size;
}


size_t Communication::HiTerm::MonTab::Entry::Write (DataStream& os) const
{
	size_t size = 0u;

	for (size_t i = 0u; i < NameFieldLength; ++i) {
		UInt16 data = i < name.size () ? name[i] : 0u;
		size += ::Write (os, data, ByteOrder::MSBFirst);
	}

	size += ::Write (os, unit, ByteOrder::MSBFirst);
	size += ::Write (os, type, ByteOrder::MSBFirst);

	size += ::WriteCDAB (os, ptr);
	size += ::WriteCDAB (os, pMax);
	size += ::WriteCDAB (os, pMin);

	if (size != GetSize ()) {
		TODO; // #TODO_ExceptionHandling
	}

	return size;
}


UInt16 Communication::HiTerm::MonTab::GetLength () const
{
	static_assert (Entry::GetSize () == 2u * Entry::NameFieldLength + 16u);
	return static_cast<UInt16> (entries.size () * Entry::GetSize ()); // #ToDo: check max UInt16
}


size_t Communication::HiTerm::MonTab::ReadData (DataStream& ds, UInt16 length)
{
	entries.clear ();
	size_t size = 0u;
	for (; size < length; ) {
		Entry entry (ForDeserialization);
		size += entry.Read (ds);
		if (size > length) {
			TODO; // #TODO_ExceptionHandling
		}
		entries.push_back (entry);
	}
	return size;
}


size_t Communication::HiTerm::MonTab::WriteData (DataStream& ds) const
{
	size_t size = 0u;
	for (auto& entry : entries) {
		size += entry.Write (ds);
	}
	return size;
}