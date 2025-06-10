#pragma once
#ifndef Communication__HiTerm_Command_ReadTabNames__hpp
#define Communication__HiTerm_Command_ReadTabNames__hpp

// #Standard
#include <string>

// #Communication
#include "Protocols\HiTerm\DataUnits\Message.hpp"


namespace Communication::HiTerm {

class ReadTabNames {
public:
	class Command;
	class Response;

private:
	static UInt8 GetID ();
};


class COMMUNICATION_EXPORT ReadTabNames::Command final : public Message::CommandBase {
public:
	explicit Command (DeserializationSelector);
	explicit Command (UInt8 key);

private:
	virtual Command*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;
};


class COMMUNICATION_EXPORT ReadTabNames::Response final : public Message::ResponseBase {
public:
	explicit Response (DeserializationSelector);
	explicit Response (UInt8 key, const std::string& name);

private:
	virtual Response*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;

private:
	std::string name;
};

}


#endif