#include "ReadBlackboxContent.hpp"

// #Kernel
#include "Utilities\Debug.hpp"

// #Communication
#include "Protocols\HiTerm\HiTermCommandIDs.hpp"


UInt8 Communication::HiTerm::ReadBlackboxContent::GetID ()
{
	return HiTerm::CommandID::READ_BBX_NEW;
}


Communication::HiTerm::ReadBlackboxContent::Command::Command (DeserializationSelector ds)
	: CommandBase	(ds)
	, info			(ds)
{
}


Communication::HiTerm::ReadBlackboxContent::Command::Command (UInt8 key, const BlackboxContent::Info& info)
	: CommandBase	(key)
	, info			(info)
{
}


Communication::HiTerm::ReadBlackboxContent::Command* Communication::HiTerm::ReadBlackboxContent::Command::New (DeserializationSelector ds) const
{
	return new Command (ds);
}


UInt8 Communication::HiTerm::ReadBlackboxContent::Command::GetID () const
{
	return ReadBlackboxContent::GetID ();
}


UInt16 Communication::HiTerm::ReadBlackboxContent::Command::GetLength () const
{
	constexpr size_t size = BlackboxContent::Info::GetSize ();
	static_assert (size == 6u);
	return size;
}


size_t Communication::HiTerm::ReadBlackboxContent::Command::ReadData (DataStream& ds, UInt16 length)
{
	if (BlackboxContent::Info::GetSize () != length) {
		TODO; // #TODO_ExceptionHandling
	}
	return info.Read (ds);
}


size_t Communication::HiTerm::ReadBlackboxContent::Command::WriteData (DataStream& ds) const
{
	return info.Write (ds);
}


Communication::HiTerm::ReadBlackboxContent::Response::Response (DeserializationSelector ds)
	: ResponseBase	(ds)
	, content		(ds)
{
}


Communication::HiTerm::ReadBlackboxContent::Response::Response (UInt8 key, const BlackboxContent& content)
	: ResponseBase	(key)
	, content		(content)
{
}


Communication::HiTerm::ReadBlackboxContent::Response* Communication::HiTerm::ReadBlackboxContent::Response::New (DeserializationSelector ds) const
{
	return new Response (ds);
}


UInt8 Communication::HiTerm::ReadBlackboxContent::Response::GetID () const
{
	return ReadBlackboxContent::GetID ();
}


UInt16 Communication::HiTerm::ReadBlackboxContent::Response::GetLength () const
{
	return static_cast<UInt16> (content.GetSize ());
}


size_t Communication::HiTerm::ReadBlackboxContent::Response::ReadData (DataStream& ds, UInt16 length)
{
	const size_t size = content.Read (ds);
	if (size != length) {
		TODO; // #TODO_ExceptionHandling
	}
	return size;
}


size_t Communication::HiTerm::ReadBlackboxContent::Response::WriteData (DataStream& ds) const
{
	return content.Write (ds);
}