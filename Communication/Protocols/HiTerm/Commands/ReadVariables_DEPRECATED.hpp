#pragma once
#ifndef Communication__HiTerm_Command_ReadVariables_DEPRECATED__hpp
#define Communication__HiTerm_Command_ReadVariables_DEPRECATED__hpp

// #Communication
#include "Protocols\HiTerm\CommandData\HiTermVariable.hpp"
#include "Protocols\HiTerm\DataUnits\Message.hpp"
#include "Protocols\HiTerm\Types\MemoryEntries.hpp"


namespace Communication::HiTerm::Deprecated {

class ReadVariables {
public:
	class Command;
	class Response;

private:
	static UInt8 GetID ();
};


class COMMUNICATION_EXPORT ReadVariables::Command final : public Message::CommandBase {
public:
	explicit Command (DeserializationSelector);
	explicit Command (UInt8 key, const MemoryEntries& memoryEntries);

private:
	virtual Command*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;

private:
	MemoryEntries memoryEntries;
};


class COMMUNICATION_EXPORT ReadVariables::Response final : public Message::ResponseBase {
public:
	explicit Response (DeserializationSelector);
	explicit Response (UInt8 key, const Variables& variables);

	const Variables&	GetVariables	() const { return variables; }

private:
	virtual Response*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;

private:
	Variables variables;
};

}


#endif