#include "Ping.hpp"

// #Standard
#include <stdexcept>

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Utilities\Debug.hpp"
#include "Utilities\Memory.hpp"

// #Communication
#include "Protocols\HiTerm\HiTermCommandIDs.hpp"


UInt8 Communication::HiTerm::Ping::GetID ()
{
	return HiTerm::CommandID::PING;
}


Communication::HiTerm::Ping::Command* Communication::HiTerm::Ping::Command::New (DeserializationSelector ds) const
{
	return MakeRaw<Command> (ds);
}


UInt8 Communication::HiTerm::Ping::Command::GetID () const
{
	return Ping::GetID ();
}


UInt16 Communication::HiTerm::Ping::Command::GetLength () const
{
	return 0u;
}


size_t Communication::HiTerm::Ping::Command::ReadData (DataStream& /*ds*/, UInt16 length)
{
	if (length != 0u) {
		TODO; // #TODO_ExceptionHandling
	}

	return 0u;
}


size_t Communication::HiTerm::Ping::Command::WriteData (DataStream& /*ds*/) const
{
	return 0u;
}


Communication::HiTerm::Ping::Response::Response (DeserializationSelector ds)
	: ResponseBase (ds)
{
}


Communication::HiTerm::Ping::Response::Response (UInt8 key, Status status)
	: ResponseBase	(key)
	, status		(status)
{
}


Communication::HiTerm::Ping::Response* Communication::HiTerm::Ping::Response::New (DeserializationSelector ds) const
{
	return MakeRaw<Response> (ds);
}


UInt8 Communication::HiTerm::Ping::Response::GetID () const
{
	return Ping::GetID ();
}


UInt16 Communication::HiTerm::Ping::Response::GetLength () const
{
	return 1u;
}


size_t Communication::HiTerm::Ping::Response::ReadData (DataStream& ds, UInt16 length)
{
	if (length != 1u) {
		TODO; // #TODO_ExceptionHandling
	}

	const size_t size = ::Read (ds, status);

	switch (status) {
	case AppRun:
	case BootRunChkOk:
	case BootRunChkNotOk:
	case FlashApiRun:
		break;
	default:
		TODO; // #TODO_ExceptionHandling
	}

	return size;
}


size_t Communication::HiTerm::Ping::Response::WriteData (DataStream& ds) const
{
	return ::Write (ds, status);
}


std::string Communication::HiTerm::ToString (Ping::Response::Status status)
{
	switch (status) {
	case Ping::Response::AppRun:			return "Application is running.";
	case Ping::Response::BootRunChkOk:		return "Booting, CHK is OK.";		// #TODO ???
	case Ping::Response::BootRunChkNotOk:	return "Booting, CHK is NOT OK.";	// #TODO ???
	case Ping::Response::FlashApiRun:		return "Flash API is running.";		// #TODO ???
	default:
		break;
	}
	throw std::invalid_argument ("{7B56DF1E-8076-4DCA-A8C9-96AEEFAC95B1}");
}