#pragma once
#ifndef Network__IODeviceProvider__hpp
#define Network__IODeviceProvider__hpp

// #ExportHeader
#include "NetworkExport.hpp"

// #Network
#include "NetworkTypes.hpp"


namespace Network {

class NETWORK_EXPORT IODeviceProvider {
public:
	virtual ~IODeviceProvider ();

	virtual void		Connect		() = 0;
	virtual void		Disconnect	() = 0;
	virtual QIODevice&	IODevice	() = 0;
	virtual bool		HasError	() const = 0;
};

}


#endif