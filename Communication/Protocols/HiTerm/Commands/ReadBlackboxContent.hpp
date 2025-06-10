#pragma once
#ifndef Communication__HiTerm_Command_ReadBlackboxContent__hpp
#define Communication__HiTerm_Command_ReadBlackboxContent__hpp

// #Communication
#include "Protocols\HiTerm\CommandData\BlackboxContent.hpp"
#include "Protocols\HiTerm\DataUnits\Message.hpp"


namespace Communication::HiTerm {

class ReadBlackboxContent {
public:
	class Command;
	class Response;

private:
	static UInt8 GetID ();
};


class COMMUNICATION_EXPORT ReadBlackboxContent::Command final : public Message::CommandBase {
public:
	explicit Command (DeserializationSelector);
	explicit Command (UInt8 key, const BlackboxContent::Info& info);

private:
	virtual Command*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;

private:
	BlackboxContent::Info info;
};


class COMMUNICATION_EXPORT ReadBlackboxContent::Response final : public Message::ResponseBase {
public:
	explicit Response (DeserializationSelector);
	explicit Response (UInt8 key, const BlackboxContent& content);

	const BlackboxContent&	GetContent	() const { return content; }

private:
	virtual Response*		New			(DeserializationSelector) const;
	virtual UInt8			GetID		() const override;
	virtual UInt16			GetLength	() const override;
	virtual size_t			ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t			WriteData	(DataStream& ds) const override;

private:
	BlackboxContent content;
};

}


#endif