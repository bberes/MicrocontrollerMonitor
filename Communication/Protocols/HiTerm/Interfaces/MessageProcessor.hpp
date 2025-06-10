#pragma once
#ifndef Communication__HiTerm_MessageProcessor__hpp
#define Communication__HiTerm_MessageProcessor__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Communication
#include "CommunicationTypes.hpp"


namespace Communication::HiTerm {

class COMMUNICATION_EXPORT MessageProcessor {
public:
	explicit MessageProcessor (Response& response);
	virtual ~MessageProcessor ();

	void			Process		(const Message& message);

private:
	virtual void	ProcessImpl	(const Message& message) = 0;

private:
	Response& response;
};

}


#endif