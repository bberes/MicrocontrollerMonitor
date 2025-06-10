#pragma once
#ifndef Communication__HiTerm_Command_Reboot__hpp
#define Communication__HiTerm_Command_Reboot__hpp

// #Communication
#include "Protocols\HiTerm\DataUnits\Message.hpp"


namespace Communication::HiTerm {

class Reboot {
public:
	class Command;
	class Response;

private:
	static UInt8 GetID ();
};


class COMMUNICATION_EXPORT Reboot::Command final : public Message::CommandBase {
public:
	using CommandBase::CommandBase;

private:
	virtual Command*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;
};


class COMMUNICATION_EXPORT Reboot::Response final : public Message::ResponseBase {
public:
	using ResponseBase::ResponseBase;

private:
	virtual Response*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;
};

}


#endif