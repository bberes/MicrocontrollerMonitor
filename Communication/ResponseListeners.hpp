#pragma once
#ifndef Communication__ResponseListeners__hpp
#define Communication__ResponseListeners__hpp

// #Standard
#include <string> // #ToDo: remove (use enum instead of string)

// #Kernel
#include "Utilities\Observer.hpp"

// #Communication
#include "CommunicationTypes.hpp"


namespace Communication {

class PingResponseListener : public Utilities::Observer {
private:
	friend PingResponse;
	virtual void Update (const std::string& status) = 0;
};


class TabDataResponseListener : public Utilities::Observer {
private:
	friend TabDataResponse;
	virtual void Update (const TabDataEntries& entries) = 0;
};


class TabValuesResponseListener : public Utilities::Observer {
private:
	friend TabValuesResponse;
	virtual void Update (const TabValues& values) = 0;
};


class ReadArrayResponseListener : public Utilities::Observer {
private:
	friend ReadArrayResponse;
	virtual void Update (const std::vector<UInt32>& variables) = 0; // #ToDo: temporary type
};


class ReadVariablesResponseListener : public Utilities::Observer {
private:
	friend ReadVariablesResponse;
	virtual void Update (const Variables& variables) = 0;
};


class WriteVariablesResponseListener : public Utilities::Observer {
private:
	friend WriteVariablesResponse;
	virtual void Update () = 0;
};

}


#endif