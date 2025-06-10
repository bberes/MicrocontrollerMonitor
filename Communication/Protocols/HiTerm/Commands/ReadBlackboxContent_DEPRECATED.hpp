#pragma once
#ifndef Communication__HiTerm_Command_ReadBlackboxContent_DEPRECATED__hpp
#define Communication__HiTerm_Command_ReadBlackboxContent_DEPRECATED__hpp

// #Communication
#include "Protocols\HiTerm\CommandData\BlackboxContent_DEPRECATED.hpp"
#include "Protocols\HiTerm\DataUnits\Message.hpp"


namespace Communication::HiTerm::Deprecated {

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
	explicit Command (UInt8 key, const Preferred::Info& info);

private:
	virtual Command*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;

private:
	Preferred::Info info;
};


class COMMUNICATION_EXPORT ReadBlackboxContent::Response final : public Message::ResponseBase {
public:
	explicit Response (DeserializationSelector);
	explicit Response (UInt8 key, const Deprecated::BlackboxContent& content);

	const Deprecated::BlackboxContent& GetContent () const { return content; }

private:
	virtual Response*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;

private:
	Deprecated::BlackboxContent content;
};

}


#endif