#include "BlackboxContent_DEPRECATED.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"


Communication::HiTerm::Deprecated::BlackboxContent::BlackboxContent (DeserializationSelector ds)
	: Deserializable	(ds)
	, info				(ds)
{
}


Communication::HiTerm::Deprecated::BlackboxContent::BlackboxContent (const Preferred::Info& info, const Preferred::Content& content)
	: Deserializable	(RegularConstructor)
	, info				(info)
	, content			(content)
{
	if (info.GetLength () / 2u != content.size ()) {
		TODO; // #TODO_ExceptionHandling
	}
	if (content.size () > Preferred::Info::MaxLength ()) {
		TODO; // #TODO_ExceptionHandling
	}
}


size_t Communication::HiTerm::Deprecated::BlackboxContent::Read (DataStream& is)
{
	size_t size = info.Read (is);
	for (UInt16 i = 0u; i < info.GetLength () / 2u; ++i) {
		UInt16 dataLow = 0u, dataHigh = 0u;
		size += ::Read (is, dataLow, ByteOrder::MSBFirst);
		size += ::Read (is, dataHigh, ByteOrder::MSBFirst);
		UInt32 data = dataHigh;
		data = (data << 16) | dataLow;
		content.push_back (data);
	}
	return size;
}


size_t Communication::HiTerm::Deprecated::BlackboxContent::Write (DataStream& os) const
{
	size_t size = info.Write (os);
	for (auto& data : content) {
		UInt16 dataLow = /*static_cast<UInt16>*/ (data), dataHigh = (data >> 16);
		size += ::Write (os, dataLow, ByteOrder::MSBFirst);
		size += ::Write (os, dataHigh, ByteOrder::MSBFirst);
	}
	return size;
}


size_t Communication::HiTerm::Deprecated::BlackboxContent::GetSize () const
{
	return info.GetSize () + sizeof (UInt32) * content.size ();
}