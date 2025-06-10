#pragma once
#ifndef Communication__HiTermProtocol__hpp
#define Communication__HiTermProtocol__hpp

// #Communication
#include "CommunicationProtocol.hpp"


namespace Communication {

class COMMUNICATION_EXPORT HiTermProtocol final : public Protocol {
public:
	HiTermProtocol ();
	virtual ~HiTermProtocol () override;

	HiTermProtocol (const HiTermProtocol&)						= delete;
	HiTermProtocol&	operator=			(const HiTermProtocol&)	= delete;

private:
	virtual ByteArray	ConvertToBytes	(const PingRequest&				request) override;
	virtual ByteArray	ConvertToBytes	(const TabDataRequest&			request) override;
	virtual ByteArray	ConvertToBytes	(const TabValuesRequest&		request) override;
	virtual ByteArray	ConvertToBytes	(const ReadVariablesRequest&	request) override;
	virtual ByteArray	ConvertToBytes	(const WriteVariablesRequest&	request) override;
	virtual ByteArray	ConvertToBytes	(const ReadArrayRequest&		request) override;

private:
	virtual void		Process			(ByteArray& byteArray) override;

private:
	class Impl;
	Owner<Impl> impl;
};

}


#endif