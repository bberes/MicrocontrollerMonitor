#pragma once
#ifndef Communication__HiTerm_Command_WriteVariables__hpp
#define Communication__HiTerm_Command_WriteVariables__hpp

// #Communication
#include "Protocols\HiTerm\CommandData\HiTermVariable.hpp"
#include "Protocols\HiTerm\DataUnits\Message.hpp"


namespace Communication::HiTerm {

class WriteVariables {
public:
	class Command;
	class Response;

private:
	static UInt8 GetID ();
};


class COMMUNICATION_EXPORT WriteVariables::Command final : public Message::CommandBase {
public:
	explicit Command (DeserializationSelector);
	explicit Command (UInt8 key, const Variables& variables);

private:
	virtual Command*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;

private:
	Variables variables;
};


class COMMUNICATION_EXPORT WriteVariables::Response final : public Message::ResponseBase {
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