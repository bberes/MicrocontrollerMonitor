#pragma once
#ifndef Communication__Connection__hpp
#define Communication__Connection__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "Types\Owner.hpp"
#include "KernelTypes.hpp"

// #Network
#include "NetworkTypes.hpp"

// #Communication
#include "CommunicationTypes.hpp"


namespace Communication {

class COMMUNICATION_EXPORT Connection final {
public:
	explicit Connection (Utilities::Logger& logger);
	~Connection ();

	Connection (const Connection&)				= delete;
	Connection&	operator=	(const Connection&)	= delete;

	bool		HasProtocol	() const;
	void		SetProtocol	(Owner<Protocol> protocol);
	Protocol&	GetProtocol	();

	void		Reset		(Owner<Network::IODeviceProvider> provider);
	void		Connect		();
	void		Disconnect	();

private:
	Utilities::Logger&					logger;
	Owner<Protocol>						protocol;
	const Owner<Network::DataReceiver>	receiver;
	Owner<Network::Connector>			connector;
};

}


#endif