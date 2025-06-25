#pragma once
#ifndef Communication__HiTerm_Command_ReadMonTab__hpp
#define Communication__HiTerm_Command_ReadMonTab__hpp

// #Communication
#include "Protocols\HiTerm\CommandData\MonTab.hpp"
#include "Protocols\HiTerm\CommandData\MonTabIndex.hpp"
#include "Protocols\HiTerm\DataUnits\Message.hpp"


namespace Communication::HiTerm {

class ReadMonTab {
public:
	class Command;
	class Response;

private:
	static UInt8 GetID (MonTabIndex index);
};


class COMMUNICATION_EXPORT ReadMonTab::Command final : public Message::CommandBase {
public:
	explicit Command (DeserializationSelector);
	explicit Command (UInt8 key, MonTabIndex index);

	inline void			SetTabIndex	(MonTabIndex index);

private:
	virtual Command*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;

private:
	MonTabIndex index;
};


class COMMUNICATION_EXPORT ReadMonTab::Response final : public Message::ResponseBase {
public:
	explicit Response (DeserializationSelector);
	explicit Response (UInt8 key, MonTabIndex index, const MonTab& monTab);

	inline void			SetTabIndex	(MonTabIndex index);
	const MonTab&		GetMonTab	() const { return monTab; }

private:
	virtual Response*	New			(DeserializationSelector) const;
	virtual UInt8		GetID		() const override;
	virtual UInt16		GetLength	() const override;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t		WriteData	(DataStream& ds) const override;

private:
	MonTabIndex	index;
	MonTab		monTab;
};

}


inline void Communication::HiTerm::ReadMonTab::Command::SetTabIndex (MonTabIndex index)
{
	CheckTabIndex (index);
	this->index = index;
}


inline void Communication::HiTerm::ReadMonTab::Response::SetTabIndex (MonTabIndex index)
{
	CheckTabIndex (index);
	this->index = index;
}


#endif