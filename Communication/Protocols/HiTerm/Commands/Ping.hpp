#pragma once
#ifndef Communication__HiTerm_Command_Ping__hpp
#define Communication__HiTerm_Command_Ping__hpp

// #Standard
#include <string>

// #Communication
#include "Protocols\HiTerm\DataUnits\Message.hpp"


namespace Communication::HiTerm {

class Ping {
public:
	class Command;
	class Response;

private:
	static UInt8 GetID ();
};


class COMMUNICATION_EXPORT Ping::Command final : public Message::CommandBase {
public:
	using CommandBase::CommandBase;

private:
	virtual Command*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;
};


class COMMUNICATION_EXPORT Ping::Response final : public Message::ResponseBase {
public:
	enum Status : UInt8 {
		AppRun			= 0u,
		BootRunChkOk	= 1u,
		BootRunChkNotOk	= 2u,
		FlashApiRun		= 3u
	};

	explicit Response (DeserializationSelector);
	explicit Response (UInt8 key, Status status);

	inline Status		GetStatus	() const { return status; }

private:
	virtual Response*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;

private:
	Status status;
};


std::string	ToString (Ping::Response::Status status);

}


#endif