#include "MessageProcessor.hpp"

// #Communication
#include "Responses.hpp"


Communication::HiTerm::MessageProcessor::MessageProcessor (Response& response)
	: response (response)
{
}


Communication::HiTerm::MessageProcessor::~MessageProcessor () = default;


void Communication::HiTerm::MessageProcessor::Process (const Message& message)
{
	ProcessImpl (message);
	response.Ready ();
}