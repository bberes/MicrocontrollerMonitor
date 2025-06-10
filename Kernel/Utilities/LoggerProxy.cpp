#include "LoggerProxy.hpp"


Utilities::LoggerProxy::LoggerProxy ()
	: logger (nullptr)
{
}


Utilities::LoggerProxy::~LoggerProxy () = default;


void Utilities::LoggerProxy::SetLogger (Logger* logger)
{
	this->logger = logger;
}


void Utilities::LoggerProxy::SetLogLevel (LogLevel level)
{
	if (logger == nullptr) {
		return;
	}
	logger->SetLogLevel (level);
}


void Utilities::LoggerProxy::LogInfo (const std::string& guid, const std::string& m)
{
	if (logger == nullptr) {
		return;
	}
	logger->LogInfo (guid, m);
}


void Utilities::LoggerProxy::LogWarning (const std::string& guid, const std::string& w, const std::exception* ex)
{
	if (logger == nullptr) {
		return;
	}
	logger->LogWarning (guid, w, ex);
}


void Utilities::LoggerProxy::LogError (const std::string& guid, const std::string& e, const std::exception* ex)
{
	if (logger == nullptr) {
		return;
	}
	logger->LogError (guid, e, ex);
}