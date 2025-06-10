#include "SiMonCommands.hpp"

// #Kernel
#include "Utilities\Debug.hpp"

// #Communication
#include "SiMonCommandIDs.hpp"


#pragma region ReadVariable
UInt8 Communication::SiMon::ReadVariable::GetID () const
{
	return CommandID::ReadVariable;
}


UInt16 Communication::SiMon::ReadVariable::GetLength () const
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::ReadVariable::ReadData (DataStream& ds, UInt16 length)
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::ReadVariable::WriteData (DataStream& ds) const
{
	TODO; // #TODO_Implement
}
#pragma endregion


#pragma region WriteVariable
UInt8 Communication::SiMon::WriteVariable::GetID () const
{
	return CommandID::WriteVariable;
}


UInt16 Communication::SiMon::WriteVariable::GetLength () const
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::WriteVariable::ReadData (DataStream& ds, UInt16 length)
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::WriteVariable::WriteData (DataStream& ds) const
{
	TODO; // #TODO_Implement
}
#pragma endregion


#pragma region ReadBBXData
UInt8 Communication::SiMon::ReadBBXData::GetID () const
{
	return CommandID::ReadBBXData;
}


UInt16 Communication::SiMon::ReadBBXData::GetLength () const
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::ReadBBXData::ReadData (DataStream& ds, UInt16 length)
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::ReadBBXData::WriteData (DataStream& ds) const
{
	TODO; // #TODO_Implement
}
#pragma endregion


#pragma region Reboot
UInt8 Communication::SiMon::Reboot::GetID () const
{
	return CommandID::Reboot;
}


UInt16 Communication::SiMon::Reboot::GetLength () const
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::Reboot::ReadData (DataStream& ds, UInt16 length)
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::Reboot::WriteData (DataStream& ds) const
{
	TODO; // #TODO_Implement
}
#pragma endregion


#pragma region ClearSector
UInt8 Communication::SiMon::ClearSector::GetID () const
{
	return CommandID::ClearSector;
}


UInt16 Communication::SiMon::ClearSector::GetLength () const
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::ClearSector::ReadData (DataStream& ds, UInt16 length)
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::ClearSector::WriteData (DataStream& ds) const
{
	TODO; // #TODO_Implement
}
#pragma endregion


#pragma region ProgramAPI
UInt8 Communication::SiMon::ProgramAPI::GetID () const
{
	return CommandID::ProgramAPI;
}


UInt16 Communication::SiMon::ProgramAPI::GetLength () const
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::ProgramAPI::ReadData (DataStream& ds, UInt16 length)
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::ProgramAPI::WriteData (DataStream& ds) const
{
	TODO; // #TODO_Implement
}
#pragma endregion


#pragma region ProgramBOOT
UInt8 Communication::SiMon::ProgramBOOT::GetID () const
{
	return CommandID::ProgramBOOT;
}


UInt16 Communication::SiMon::ProgramBOOT::GetLength () const
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::ProgramBOOT::ReadData (DataStream& ds, UInt16 length)
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::ProgramBOOT::WriteData (DataStream& ds) const
{
	TODO; // #TODO_Implement
}
#pragma endregion


#pragma region ProgramApp
UInt8 Communication::SiMon::ProgramApp::GetID () const
{
	return CommandID::ProgramApp;
}


UInt16 Communication::SiMon::ProgramApp::GetLength () const
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::ProgramApp::ReadData (DataStream& ds, UInt16 length)
{
	TODO; // #TODO_Implement
}


size_t Communication::SiMon::ProgramApp::WriteData (DataStream& ds) const
{
	TODO; // #TODO_Implement
}
#pragma endregion


#pragma region Ping
UInt8 Communication::SiMon::Ping::GetID () const
{
	return CommandID::Ping;
}


UInt16 Communication::SiMon::Ping::GetLength () const
{
	return 0u;
}


size_t Communication::SiMon::Ping::ReadData (DataStream& ds, UInt16 length)
{
	if (length != 0u) {
		TODO; // #TODO_ExceptionHandling
	}

	return 0u;
}


size_t Communication::SiMon::Ping::WriteData (DataStream& /*ds*/) const
{
	return 0u;
}
#pragma endregion