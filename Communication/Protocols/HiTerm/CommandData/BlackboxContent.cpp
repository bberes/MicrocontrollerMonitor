#include "BlackboxContent.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"
#include "KernelTypes.hpp"


Communication::HiTerm::BlackboxContent::Info::Info (DeserializationSelector ds)
	: Deserializable (ds)
{
}


Communication::HiTerm::BlackboxContent::Info::Info (UInt32 address, UInt16 length)
	: Deserializable	(RegularConstructor)
	, address			(address)
	, length			(length)
{
}


size_t Communication::HiTerm::BlackboxContent::Info::Read (DataStream& is)
{
	size_t size = 0u;
	size += ::Read (is, address, ByteOrder::MSBFirst);
	size += ::Read (is, length, ByteOrder::MSBFirst);
	return size;
}


size_t Communication::HiTerm::BlackboxContent::Info::Write (DataStream& os) const
{
	size_t size = 0u;
	size += ::Write (os, address, ByteOrder::MSBFirst);
	size += ::Write (os, length, ByteOrder::MSBFirst);
	return size;
}


Communication::HiTerm::BlackboxContent::BlackboxContent (DeserializationSelector ds)
	: Deserializable	(ds)
	, info				(ds)
{
}


Communication::HiTerm::BlackboxContent::BlackboxContent (UInt32 address, const Content& content)
	: Deserializable	(RegularConstructor)
	, info				(address, static_cast<UInt16> (content.size ()))
	, content			(content)
{
	if (content.size () > Info::MaxLength ()) {
		TODO; // #TODO_ExceptionHandling
	}
}


size_t Communication::HiTerm::BlackboxContent::Read (DataStream& is)
{
	size_t size = info.Read (is);
	for (UInt16 i = 0u; i < info.GetLength (); ++i) {
		UInt32 data = 0u;
		size += ::Read (is, data, ByteOrder::MSBFirst);
		content.push_back (data);
	}
	return size;
}


size_t Communication::HiTerm::BlackboxContent::Write (DataStream& os) const
{
	size_t size = info.Write (os);
	for (auto& data : content) {
		size += ::Write (os, data, ByteOrder::MSBFirst);
	}
	return size;
}


size_t Communication::HiTerm::BlackboxContent::GetSize () const
{
	return info.GetSize () + sizeof (UInt32) * content.size ();
}