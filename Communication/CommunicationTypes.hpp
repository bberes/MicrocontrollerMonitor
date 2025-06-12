#pragma once
#ifndef Communication__CommunicationTypes__hpp
#define Communication__CommunicationTypes__hpp

// #Standard
#include <vector>

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication {

	class Connection;
	class Protocol;


	// #RequestRelatedTypes

	class Request;
	class Response;

	class PingRequest;
	class PingResponse;
	class PingResponseListener;

	class ReadArrayRequest;
	class ReadArrayResponse;
	class ReadArrayResponseListener;

	class ReadVariablesRequest;
	class ReadVariablesResponse;
	class ReadVariablesResponseListener;

	class TabDataRequest;
	class TabDataResponse;
	class TabDataResponseListener;

	class TabValuesRequest;
	class TabValuesResponse;
	class TabValuesResponseListener;

	class WriteVariablesRequest;
	class WriteVariablesResponse;
	class WriteVariablesResponseListener;


	// #DataTypesOfRequests

	class MemoryReference;
	class Variable;

	struct TabDataEntry;

	using MemoryRef			= MemoryReference;
	using MemoryRefs		= std::vector<MemoryRef>;
	using TabDataEntries	= std::vector<TabDataEntry>;
	using TabValues			= std::vector<UInt32>;
	using Variables			= std::vector<Variable>;

}


namespace Communication::HiTerm {
	class Frame;
	class FrameProcessor;
	class Message;
	class MessageProcessor;
	class MessageReceiver;
	class MessageStore;
	class MessageTypeID;
	class Packet;
	class PacketProcessor;
	class ProcessorID;

	class Memory;
	class Variable;

	using MemoryEntries	= std::vector<Memory>;
	using Values		= std::vector<UInt32>;
	using Variables		= std::vector<Variable>;
}


#endif