#pragma once
#ifndef Communication__HiTerm_MessageDispatcher__hpp
#define Communication__HiTerm_MessageDispatcher__hpp

// #Kernel
#include "Types\BaseTypes.hpp"
#include "Types\HashTable.hpp"
#include "Types\Owner.hpp"

// #Communication
#include "Protocols\HiTerm\Interfaces\MessageReceiver.hpp"
#include "CommunicationTypes.hpp"


namespace Communication::HiTerm {

class MessageDispatcher final : public MessageReceiver {
public:
	virtual ~MessageDispatcher () override;

	void			Add			(UInt8 processorID, const Message& message, Owner<MessageProcessor> mp);
	bool			Contains	(UInt8 processorID, const Message& message);

private:
	virtual void	Receive		(const Message& message, const ProcessorID& id) override;

private:
	HashTable<UInt32, Owner<MessageProcessor>> processors;
};

}


#endif