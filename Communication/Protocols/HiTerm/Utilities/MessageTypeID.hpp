#pragma once
#ifndef Communication__HiTerm_MessageTypeID__hpp
#define Communication__HiTerm_MessageTypeID__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "Types\BaseTypes.hpp"

// #Communication
#include "Protocols\HiTerm\Utilities\DeviceRole.hpp"
#include "Protocols\HiTerm\Utilities\MessageType.hpp"


namespace Communication::HiTerm {

class COMMUNICATION_EXPORT MessageTypeID final {
public:
	explicit MessageTypeID (MessageType type, UInt8 id);
	explicit MessageTypeID (DeviceRole role, UInt8 id);

	operator UInt16 () const;

private:
	UInt16 typeID;
};

}


#endif