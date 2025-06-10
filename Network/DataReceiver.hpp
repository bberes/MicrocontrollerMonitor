#pragma once
#ifndef Network__DataReceiver__hpp
#define Network__DataReceiver__hpp

// #Kernel
#include "KernelTypes.hpp"
#include "Types\ByteArray.hpp"

// #Network
#include "Interfaces\Receiver.hpp"
#include "NetworkTypes.hpp"


namespace Network {

class NETWORK_EXPORT DataReceiver final : public Receiver {
public:
	explicit DataReceiver (Utilities::Logger& logger);
	virtual ~DataReceiver () override;

	void			Set			(DataProcessor& dp);

private:
	virtual void	Receive		(const ByteArray& byteArray) override;

private:
	Utilities::Logger&	logger;
	ByteArray			buffer;
	DataProcessor*		processor;
};

}


#endif