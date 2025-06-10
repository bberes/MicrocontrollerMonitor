#pragma once
#ifndef Communication__HiTerm_MessageReceiver__hpp
#define Communication__HiTerm_MessageReceiver__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Communication
#include "CommunicationTypes.hpp"


namespace Communication::HiTerm {

class COMMUNICATION_EXPORT MessageReceiver {
public:
	virtual ~MessageReceiver ();

	virtual void Receive (const Message& message, const ProcessorID& id) = 0;
};

}


#endif