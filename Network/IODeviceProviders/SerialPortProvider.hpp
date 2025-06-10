#pragma once
#ifndef Network__SerialPortProvider__hpp
#define Network__SerialPortProvider__hpp

// #ExportHeader
#include "NetworkExport.hpp"

// #Kernel
#include "Types\Owner.hpp"

// #Network
#include "Interfaces\IODeviceProvider.hpp"
#include "NetworkTypes.hpp"


namespace Network {

class NETWORK_EXPORT SerialPortProvider final : public IODeviceProvider {
public:
	explicit SerialPortProvider (const SerialPort::Descriptor&);
	virtual ~SerialPortProvider () override;

	void				Set			(const SerialPort::Descriptor&);

private:
	virtual void		Connect		() override;
	virtual void		Disconnect	() override;
	virtual QIODevice&	IODevice	() override;
	virtual bool		HasError	() const override;

private:
	class Impl;
	Owner<Impl> impl;
};

}


#endif