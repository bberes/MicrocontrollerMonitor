#pragma once
#ifndef Network__Connector__hpp
#define Network__Connector__hpp

// #ExportHeader
#include "NetworkExport.hpp"

// #Qt
#include <QObject>

// #Kernel
#include "KernelTypes.hpp"
#include "Types\Owner.hpp"

// #Network
#include "NetworkTypes.hpp"


namespace Network {

class NETWORK_EXPORT Connector final : public QObject {
	Q_OBJECT

public:
	explicit Connector (Utilities::Logger& logger, Receiver& receiver, Owner<IODeviceProvider> provider);
	virtual ~Connector () override;

	Connector (const Connector&)					= delete;
	Connector&	operator=		(const Connector&)	= delete;

public:
	bool		IsConnected		() const;

	void		Connect			();
	void		Disconnect		();
	void		TransmitData	(const ByteArray& data);

public slots:
	void		DataReceived	();

private:
	Utilities::Logger&		logger;
	Receiver&				receiver;
	Owner<IODeviceProvider>	provider;
};

}


#endif