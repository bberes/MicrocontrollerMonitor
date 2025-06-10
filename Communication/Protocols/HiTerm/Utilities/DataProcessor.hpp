#pragma once
#ifndef Communication__HiTerm_DataProcessor__hpp
#define Communication__HiTerm_DataProcessor__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "Types\ByteArray.hpp"

// #Network
#include "Interfaces\DataProcessor.hpp"

// #Communication
#include "CommunicationTypes.hpp"


namespace Communication::HiTerm {

class COMMUNICATION_EXPORT DataProcessor final : public Network::DataProcessor {
public:
	explicit DataProcessor (FrameProcessor& processor);

private:
	virtual void	Process			(ByteArray& receivedBytes) override;
	void			FrameReceived	(const ByteArray& byteStream) const;

private:
	ByteArray		buffer;
	FrameProcessor&	processor;
};

}


#endif