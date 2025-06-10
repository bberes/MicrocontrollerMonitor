#pragma once
#ifndef Communication__WriteVariablesRequest__hpp
#define Communication__WriteVariablesRequest__hpp

// #Communication
#include "Data\Variable.hpp"
#include "CommunicationTypes.hpp"
#include "Request.hpp"


namespace Communication {

class COMMUNICATION_EXPORT WriteVariablesRequest final : public Request {
public:
	DECLARE_CLASS_NAME (Communication, WriteVariablesRequest)

	explicit WriteVariablesRequest (UInt8 processorID, const Variables& variables);

	const Variables& GetVariables () const { return variables; }

private:
	Variables variables;
};

}


#endif