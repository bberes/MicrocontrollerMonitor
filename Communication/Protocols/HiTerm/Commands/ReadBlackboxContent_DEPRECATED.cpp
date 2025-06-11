#include "ReadBlackboxContent_DEPRECATED.hpp"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"
#include "Utilities\Memory.hpp"

// #Communication
#include "Protocols\HiTerm\HiTermCommandIDs.hpp"


UInt8 Communication::HiTerm::Deprecated::ReadBlackboxContent::GetID ()
{
	return HiTerm::CommandID::READ_BBX;
}


Communication::HiTerm::Deprecated::ReadBlackboxContent::Command::Command (DeserializationSelector ds)
	: CommandBase	(ds)
	, info			(ds)
{
}


Communication::HiTerm::Deprecated::ReadBlackboxContent::Command::Command (UInt8 key, const Preferred::Info& info)
	: CommandBase	(key)
	, info			(info)
{
}


Communication::HiTerm::Deprecated::ReadBlackboxContent::Command* Communication::HiTerm::Deprecated::ReadBlackboxContent::Command::New (DeserializationSelector ds) const
{
	return MakeRaw<Deprecated::ReadBlackboxContent::Command> (ds);
}


UInt8 Communication::HiTerm::Deprecated::ReadBlackboxContent::Command::GetID () const
{
	return Deprecated::ReadBlackboxContent::GetID ();
}


UInt16 Communication::HiTerm::Deprecated::ReadBlackboxContent::Command::GetLength () const
{
	constexpr size_t size = Preferred::Info::GetSize ();
	static_assert (size == 6u);
	return size;
}


size_t Communication::HiTerm::Deprecated::ReadBlackboxContent::Command::ReadData (DataStream& ds, UInt16 length)
{
	if (Preferred::Info::GetSize () != length) {
		TODO; // #TODO_ExceptionHandling
	}
	return info.Read (ds);
}


size_t Communication::HiTerm::Deprecated::ReadBlackboxContent::Command::WriteData (DataStream& ds) const
{
	return info.Write (ds);
}


Communication::HiTerm::Deprecated::ReadBlackboxContent::Response::Response (DeserializationSelector ds)
	: ResponseBase	(ds)
	, content		(ds)
{
}


Communication::HiTerm::Deprecated::ReadBlackboxContent::Response::Response (UInt8 key, const Deprecated::BlackboxContent& content)
	: ResponseBase	(key)
	, content		(content)
{
}


Communication::HiTerm::Deprecated::ReadBlackboxContent::Response* Communication::HiTerm::Deprecated::ReadBlackboxContent::Response::New (DeserializationSelector ds) const
{
	return MakeRaw<Deprecated::ReadBlackboxContent::Response> (ds);
}


UInt8 Communication::HiTerm::Deprecated::ReadBlackboxContent::Response::GetID () const
{
	return Deprecated::ReadBlackboxContent::GetID ();
}


UInt16 Communication::HiTerm::Deprecated::ReadBlackboxContent::Response::GetLength () const
{
	return static_cast<UInt16> (content.GetSize ());
}


size_t Communication::HiTerm::Deprecated::ReadBlackboxContent::Response::ReadData (DataStream& ds, UInt16 length)
{
	const size_t size = content.Read (ds);
	if (size != length) {
		TODO; // #TODO_ExceptionHandling
	}
	return size;
}


size_t Communication::HiTerm::Deprecated::ReadBlackboxContent::Response::WriteData (DataStream& ds) const
{
	return content.Write (ds);
}