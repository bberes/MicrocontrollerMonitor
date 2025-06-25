#pragma once
#ifndef Communication__HiTerm_MessageStore__hpp
#define Communication__HiTerm_MessageStore__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "Types\BaseTypes.hpp"
#include "Types\HashTable.hpp"
#include "Types\Owner.hpp"

// #Communication
#include "CommunicationTypes.hpp"


namespace Communication::HiTerm {

class COMMUNICATION_EXPORT MessageStore final {
public:
	MessageStore (const MessageStore&)				= delete;
	MessageStore& operator= (const MessageStore&)	= delete;

	MessageStore () = default;
	~MessageStore ();

	void		Register		(const Message& message);
	bool		IsRegistered	(const Message& message) const;
	Message*	CreateNew		(const MessageTypeID& typeID) const;

private:
	HashTable<UInt16, Owner<Message>> store;
};

}


#endif