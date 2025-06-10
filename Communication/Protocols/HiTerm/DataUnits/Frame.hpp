#pragma once
#ifndef Communication__HiTerm_Frame__hpp
#define Communication__HiTerm_Frame__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "Types\ByteArray.hpp"

// #Communication
#include "CommunicationTypes.hpp"


namespace Communication::HiTerm {

class COMMUNICATION_EXPORT Frame final {
public:
	explicit Frame (const Packet& packet);
	explicit Frame (ByteArray&& byteStream);
	explicit Frame (const ByteArray& byteStream);

	operator Packet () const;
	operator const ByteArray& () const;

private:
	ByteArray frame;
};

}


#endif