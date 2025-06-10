#pragma once
#ifndef Communication__HiTerm_Packet__hpp
#define Communication__HiTerm_Packet__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "Types\ByteArray.hpp"

// #Communication
#include "Protocols\HiTerm\Types\MessagePtr.hpp"
#include "CommunicationTypes.hpp"


namespace Communication::HiTerm {

class COMMUNICATION_EXPORT Packet final {
public:
	explicit Packet (const Message& message, const ProcessorID& procID);
	explicit Packet (ByteArray&& packet);

	MessagePtr GetMessage (const MessageStore& ms, ProcessorID& procID) const;
	operator const ByteArray& () const;

private:
	ByteArray packet;
};

}


#endif