#include "ReadWrite.hpp"

// #Kernel
#include "Exceptions\KernelExceptions.hpp"


ByteOrderScope::ByteOrderScope (DataStream& ds, ByteOrder byteOrder)
	: ds				(ds)
	, originalByteOrder	(ds.byteOrder ())
{
	const bool isMSBFirst = byteOrder == ByteOrder::MSBFirst;
	ds.setByteOrder (isMSBFirst ? DataStream::ByteOrder::BigEndian : DataStream::ByteOrder::LittleEndian);
}


ByteOrderScope::~ByteOrderScope ()
{
	ds.setByteOrder (originalByteOrder);
}


static DataStreamStatus ToDataStreamStatus (DataStream::Status status)
{
	switch (status) {
	case DataStream::Status::Ok:				return DataStreamStatus::Ok;
	case DataStream::Status::ReadPastEnd:		return DataStreamStatus::ReadPastEnd;
	case DataStream::Status::ReadCorruptData:	return DataStreamStatus::ReadCorruptData;
	case DataStream::Status::WriteFailed:		return DataStreamStatus::WriteFailed;
	default:
		throw std::invalid_argument ("{4B821EAC-AF60-4281-8C0F-183205B6935C}");
	}
}


void CheckStatus (const DataStream& ds)
{
	if (ds.status () != DataStream::Status::Ok) {
		throw DataStreamError (ToDataStreamStatus (ds.status ()), "{2BBC4ED1-77C4-4162-9F2F-5EE1CADD81DE}");
	}
}


namespace {

class FPPrecisionScope final {
public:
	FPPrecisionScope (DataStream& ds, DataStream::FloatingPointPrecision precision);
	~FPPrecisionScope ();

private:
	DataStream&							ds;
	DataStream::FloatingPointPrecision	originalPrecision;
};


FPPrecisionScope::FPPrecisionScope (DataStream& ds, DataStream::FloatingPointPrecision precision)
	: ds				(ds)
	, originalPrecision	(precision)
{
	ds.setFloatingPointPrecision (precision);
}


FPPrecisionScope::~FPPrecisionScope ()
{
	ds.setFloatingPointPrecision (originalPrecision);
}

}


template <>
void ReadImpl (DataStream& ds, float& data)
{
	FPPrecisionScope scope (ds, DataStream::FloatingPointPrecision::SinglePrecision);
	ds >> data;
}


template <>
void ReadImpl (DataStream& ds, double& data)
{
	FPPrecisionScope scope (ds, DataStream::FloatingPointPrecision::DoublePrecision);
	ds >> data;
}


template <>
void WriteImpl (DataStream& ds, const float& data)
{
	FPPrecisionScope scope (ds, DataStream::FloatingPointPrecision::SinglePrecision);
	ds << data;
}


template <>
void WriteImpl (DataStream& ds, const double& data)
{
	FPPrecisionScope scope (ds, DataStream::FloatingPointPrecision::DoublePrecision);
	ds << data;
}