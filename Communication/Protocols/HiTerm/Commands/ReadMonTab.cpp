#include "ReadMonTab.hpp"

// #Kernel
#include "Utilities\Debug.hpp"

// #Communication
#include "Protocols\HiTerm\HiTermCommandIDs.hpp"


UInt8 Communication::HiTerm::ReadMonTab::GetID (MonTabIndex index)
{
	return HiTerm::CommandID::READ_MON_TAB0 + index;
}


Communication::HiTerm::ReadMonTab::Command::Command (DeserializationSelector ds)
	: CommandBase (ds)
{
}


Communication::HiTerm::ReadMonTab::Command::Command (UInt8 key, MonTabIndex index)
	: CommandBase	(key)
	, index			(index)
{
	CheckTabIndex (index);
}


Communication::HiTerm::ReadMonTab::Command* Communication::HiTerm::ReadMonTab::Command::New (DeserializationSelector ds) const
{
	auto m = new Command (ds);
	m->SetTabIndex (index);
	return m;
}


UInt8 Communication::HiTerm::ReadMonTab::Command::GetID () const
{
	return ReadMonTab::GetID (index);
}


UInt16 Communication::HiTerm::ReadMonTab::Command::GetLength () const
{
	return 0u;
}


size_t Communication::HiTerm::ReadMonTab::Command::ReadData (DataStream& /*ds*/, UInt16 length)
{
	if (length != 0u) {
		TODO; // #ExceptionHandling
	}

	return 0u;
}


size_t Communication::HiTerm::ReadMonTab::Command::WriteData (DataStream& /*ds*/) const
{
	return 0u;
}


Communication::HiTerm::ReadMonTab::Response::Response (DeserializationSelector ds)
	: ResponseBase (ds)
{
}


Communication::HiTerm::ReadMonTab::Response::Response (UInt8 key, MonTabIndex index, const MonTab& monTab)
	: ResponseBase	(key)
	, index			(index)
	, monTab		(monTab)
{
	CheckTabIndex (index);
}


Communication::HiTerm::ReadMonTab::Response* Communication::HiTerm::ReadMonTab::Response::New (DeserializationSelector ds) const
{
	auto m = new Response (ds);
	m->SetTabIndex (index);
	return m;
}


UInt8 Communication::HiTerm::ReadMonTab::Response::GetID () const
{
	return ReadMonTab::GetID (index);
}


UInt16 Communication::HiTerm::ReadMonTab::Response::GetLength () const
{
	return monTab.GetLength ();
}


size_t Communication::HiTerm::ReadMonTab::Response::ReadData (DataStream& ds, UInt16 length)
{
	return monTab.ReadData (ds, length);
}


size_t Communication::HiTerm::ReadMonTab::Response::WriteData (DataStream& ds) const
{
	return monTab.WriteData (ds);
}