#pragma once
#ifndef Communication__CommunicationTypes__hpp
#define Communication__CommunicationTypes__hpp

// #Kernel
#include "Types\BaseTypes.hpp"
#include "Types\Vector.hpp"


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
	using MemoryRefs		= Vector<MemoryRef>;
	using TabDataEntries	= Vector<TabDataEntry>;
	using TabValues			= Vector<UInt32>;
	using Variables			= Vector<Variable>;

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

	using MemoryEntries	= Vector<Memory>;
	using Values		= Vector<UInt32>;
	using Variables		= Vector<Variable>;
}


#endif