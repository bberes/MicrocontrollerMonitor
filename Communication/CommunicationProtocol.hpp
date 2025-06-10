#pragma once
#ifndef Communication__Protocol__hpp
#define Communication__Protocol__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Kernel
#include "Types\BaseTypes.hpp"
#include "Types\Owner.hpp"
#include "KernelTypes.hpp"

// #Network
#include "Interfaces\DataProcessor.hpp"
#include "NetworkTypes.hpp"

// #Communication
#include "CommunicationTypes.hpp"


namespace Communication {

class COMMUNICATION_EXPORT Protocol : public Network::DataProcessor {
public:
	Protocol ();
	virtual ~Protocol ();

	Protocol (const Protocol&)								= delete;
	Protocol&			operator=		(const Protocol&)	= delete;

	void				SetConnector	(Network::Connector& connector);
	void				SetLogger		(Utilities::Logger* logger);

	void				AddListener		(PingResponseListener&				listener);
	void				AddListener		(TabDataResponseListener&			listener);
	void				AddListener		(TabValuesResponseListener&			listener);
	void				AddListener		(ReadVariablesResponseListener&		listener);
	void				AddListener		(WriteVariablesResponseListener&	listener);
	void				AddListener		(ReadArrayResponseListener&			listener);

	template <typename RequestType>
	void				SendRequest		(const RequestType& request);

private:
	bool				CheckConnector	() const;
	void				Transmit		(const ByteArray& bytes, const Request& request);

private:
	virtual ByteArray	ConvertToBytes	(const PingRequest&				request) = 0;
	virtual ByteArray	ConvertToBytes	(const TabDataRequest&			request) = 0;
	virtual ByteArray	ConvertToBytes	(const TabValuesRequest&		request) = 0;
	virtual ByteArray	ConvertToBytes	(const ReadVariablesRequest&	request) = 0;
	virtual ByteArray	ConvertToBytes	(const WriteVariablesRequest&	request) = 0;
	virtual ByteArray	ConvertToBytes	(const ReadArrayRequest&		request) = 0;

protected:
	Owner<Utilities::LoggerProxy>	logger;

	Owner<PingResponse>				pingResponse;
	Owner<TabDataResponse>			tabDataResponse;
	Owner<TabValuesResponse>		tabValuesResponse;
	Owner<ReadVariablesResponse>	readVariablesResponse;
	Owner<WriteVariablesResponse>	writeVariablesResponse;
	Owner<ReadArrayResponse>		readArrayResponse;

private:
	Network::Connector*				connector;
};

}


template <typename RequestType>
void Communication::Protocol::SendRequest (const RequestType& request)
{
	if (!CheckConnector ()) {
		return;
	}
	Transmit (ConvertToBytes (request), request);
}


#endif