#pragma once
#ifndef Communication__HiTerm_MessageDispatcher__hpp
#define Communication__HiTerm_MessageDispatcher__hpp

// #Standard
#include <unordered_map>

// #Kernel
#include "Types\BaseTypes.hpp"

// #Communication
#include "Protocols\HiTerm\Interfaces\MessageReceiver.hpp"
#include "Protocols\HiTerm\Types\MessageProcessorPtr.hpp"


namespace Communication::HiTerm {

class MessageDispatcher final : public MessageReceiver {
public:
	virtual ~MessageDispatcher () override;

	void			Add			(UInt8 processorID, const Message& message, MessageProcessorPtr&& mp);
	bool			Contains	(UInt8 processorID, const Message& message);

private:
	virtual void	Receive		(const Message& message, const ProcessorID& id) override;

private:
	using Processors = std::unordered_map<UInt32, MessageProcessor*>;

	Processors processors;
};

}


#endif