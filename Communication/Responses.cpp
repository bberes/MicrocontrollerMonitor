#include "Responses.hpp"

// #Kernel
#include "Utilities\Logger.hpp"

// #Communication
#include "ResponseListeners.hpp"


Communication::Response::Response (Utilities::Logger& logger)
	: logger (logger)
{
}


Communication::Response::~Response () = default;


void Communication::Response::Ready () const
{
	logger.LogInfo ("{D305D751-0F70-4D7A-A75C-C339BD6ADBF9}", ClassName ());
}


void Communication::PingResponse::SetStatus (const std::string& status)
{
	for (auto& observer : GetObservers ()) {
		static_cast<PingResponseListener*> (observer)->Update (status);
	}
}


void Communication::TabDataResponse::SetEntries (const TabDataEntries& entries)
{
	for (auto& observer : GetObservers ()) {
		static_cast<TabDataResponseListener*> (observer)->Update (entries);
	}
}


void Communication::TabValuesResponse::SetValues (const TabValues& values)
{
	for (auto& observer : GetObservers ()) {
		static_cast<TabValuesResponseListener*> (observer)->Update (values);
	}
}


void Communication::ReadVariablesResponse::SetVariables (const Variables& variables)
{
	for (auto& observer : GetObservers ()) {
		static_cast<ReadVariablesResponseListener*> (observer)->Update (variables);
	}
}


void Communication::WriteVariablesResponse::Notify ()
{
	for (auto& observer : GetObservers ()) {
		static_cast<WriteVariablesResponseListener*> (observer)->Update ();
	}
}


void Communication::ReadArrayResponse::SetVariables (const std::vector<UInt32>& variables)
{
	for (auto& observer : GetObservers ()) {
		static_cast<ReadArrayResponseListener*> (observer)->Update (variables);
	}
}