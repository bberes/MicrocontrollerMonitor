#pragma once
#ifndef Communication__HiTerm_Message__hpp
#define Communication__HiTerm_Message__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "Serialization\Deserializable.hpp"
#include "Serialization\Serializable.hpp"
#include "Types\BaseTypes.hpp"

// #Communication
#include "Protocols\HiTerm\Utilities\MessageType.hpp"
#include "CommunicationTypes.hpp"


namespace Communication::HiTerm {

class COMMUNICATION_EXPORT Message
	: private Serializable
	, private Deserializable
{
public:
	class CommandBase;
	class ResponseBase;

	explicit Message (DeserializationSelector);
	explicit Message (UInt8 key);
	virtual ~Message ();

	inline UInt8		GetKey		() const;
	MessageTypeID		GetTypeID	() const;

	virtual Message*	New			(DeserializationSelector) const = 0;
	virtual MessageType	GetType		() const = 0;
	virtual UInt8		GetID		() const = 0;

	virtual size_t		Read		(DataStream& ds) override final;
	virtual size_t		Write		(DataStream& ds) const override final;

private:
	virtual UInt16		GetLength	() const = 0;
	virtual size_t		ReadData	(DataStream& ds, UInt16 length) = 0;
	virtual size_t		WriteData	(DataStream& ds) const = 0;

private:
	UInt8 key;
};


class Message::CommandBase : public Message {
public:
	using Message::Message;

private:
	virtual MessageType GetType () const override final { return MessageType::Command; }
};


class Message::ResponseBase : public Message {
public:
	using Message::Message;

private:
	virtual MessageType GetType () const override final { return MessageType::Response; }
};

}


inline UInt8 Communication::HiTerm::Message::GetKey () const
{
	return key;
}


#endif