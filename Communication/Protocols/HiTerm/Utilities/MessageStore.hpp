#pragma once
#ifndef Communication__HiTerm_MessageStore__hpp
#define Communication__HiTerm_MessageStore__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "Types\BaseTypes.hpp"
#include "Types\HashTable.hpp"

// #Communication
#include "CommunicationTypes.hpp"


namespace Communication::HiTerm {

class COMMUNICATION_EXPORT MessageStore final {
public:
	~MessageStore ();

	void		Register		(const Message& message);
	bool		IsRegistered	(const Message& message) const;
	Message*	CreateNew		(const MessageTypeID& typeID) const;

private:
	HashTable<UInt16, Message*> store;
};

}


#endif