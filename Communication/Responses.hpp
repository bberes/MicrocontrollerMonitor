#pragma once
#ifndef Communication__Responses__hpp
#define Communication__Responses__hpp

// #Standard
#include <string>

// #Kernel
#include "Types\NamedType.hpp"
#include "Utilities\Observer.hpp"
#include "KernelTypes.hpp"

// #Communication
#include "CommunicationTypes.hpp"


namespace Communication {

class Response
	: public  Utilities::Subject
	, private NamedType
{
public:
	explicit Response (Utilities::Logger& logger);
	virtual ~Response ();

	void Ready () const;

private:
	Utilities::Logger& logger;
};


class PingResponse final : public Response {
public:
	using Response::Response;
	DECLARE_CLASS_NAME (Communication, PingResponse)

	void SetStatus (const std::string& status); // #ToDo: create enum Communication::Status
};


class TabDataResponse final : public Response {
public:
	using Response::Response;
	DECLARE_CLASS_NAME (Communication, TabDataResponse)

	void SetEntries (const TabDataEntries& entries);
};


class TabValuesResponse final : public Response {
public:
	using Response::Response;
	DECLARE_CLASS_NAME (Communication, TabValuesResponse)

	void SetValues (const TabValues& values);
};


class ReadVariablesResponse final : public Response {
public:
	using Response::Response;
	DECLARE_CLASS_NAME (Communication, ReadVariablesResponse)

	void SetVariables (const Variables& variables);
};


class WriteVariablesResponse final : public Response {
public:
	using Response::Response;
	DECLARE_CLASS_NAME (Communication, WriteVariablesResponse)

	void Notify ();
};


class ReadArrayResponse final : public Response {
public:
	using Response::Response;
	DECLARE_CLASS_NAME (Communication, ReadArrayResponse)

	void SetVariables (const std::vector<UInt32>& variables);
	// #ToDo: temporary solution, create Array type (address, length, data)
};

}


#endif