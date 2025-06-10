#pragma once
#ifndef Communication__SiMon_Commands__hpp
#define Communication__SiMon_Commands__hpp

// #Communication
#include "Protocols\HiTerm\DataUnits\Message.hpp"


namespace Communication::SiMon {

class ReadVariable final : public HiTerm::Message {
public:
	using Message::Message;

private:
	virtual UInt8	GetID		() const override;
	virtual UInt16	GetLength	() const override;
	virtual size_t	ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t	WriteData	(DataStream& ds) const override;
};


class WriteVariable final : public HiTerm::Message {
public:
	using Message::Message;

private:
	virtual UInt8	GetID		() const override;
	virtual UInt16	GetLength	() const override;
	virtual size_t	ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t	WriteData	(DataStream& ds) const override;
};


class ReadBBXData final : public HiTerm::Message {
public:
	using Message::Message;

private:
	virtual UInt8	GetID		() const override;
	virtual UInt16	GetLength	() const override;
	virtual size_t	ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t	WriteData	(DataStream& ds) const override;
};


class Reboot final : public HiTerm::Message {
public:
	using Message::Message;

private:
	virtual UInt8	GetID		() const override;
	virtual UInt16	GetLength	() const override;
	virtual size_t	ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t	WriteData	(DataStream& ds) const override;
};


class ClearSector final : public HiTerm::Message {
public:
	using Message::Message;

private:
	virtual UInt8	GetID		() const override;
	virtual UInt16	GetLength	() const override;
	virtual size_t	ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t	WriteData	(DataStream& ds) const override;
};


class ProgramAPI final : public HiTerm::Message {
public:
	using Message::Message;

private:
	virtual UInt8	GetID		() const override;
	virtual UInt16	GetLength	() const override;
	virtual size_t	ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t	WriteData	(DataStream& ds) const override;
};


class ProgramBOOT final : public HiTerm::Message {
public:
	using Message::Message;

private:
	virtual UInt8	GetID		() const override;
	virtual UInt16	GetLength	() const override;
	virtual size_t	ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t	WriteData	(DataStream& ds) const override;
};


class ProgramApp final : public HiTerm::Message {
public:
	using Message::Message;

private:
	virtual UInt8	GetID		() const override;
	virtual UInt16	GetLength	() const override;
	virtual size_t	ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t	WriteData	(DataStream& ds) const override;
};


class Ping final : public HiTerm::Message {
public:
	using Message::Message;

private:
	virtual UInt8	GetID		() const override;
	virtual UInt16	GetLength	() const override;
	virtual size_t	ReadData	(DataStream& ds, UInt16 length) override;
	virtual size_t	WriteData	(DataStream& ds) const override;
};

}


#endif