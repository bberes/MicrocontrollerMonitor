#pragma once
#ifndef Kernel__ReadWrite__hpp
#define Kernel__ReadWrite__hpp

// #ExportHeader
#include "KernelExport.hpp"

// #Kernel
#include "Types\DataStream.hpp"


enum class ByteOrder {
	MSBFirst,
	LSBFirst
};


template <typename T>
size_t Read (DataStream& ds, T& data);

template <typename T>
size_t Read (DataStream& ds, T& data, ByteOrder order);

template <typename T>
size_t Write (DataStream& ds, const T& data);

template <typename T>
size_t Write (DataStream& ds, const T& data, ByteOrder order);


class KERNEL_EXPORT ByteOrderScope final {
public:
	explicit ByteOrderScope (DataStream& ds, ByteOrder byteOrder);
	~ByteOrderScope ();

private:
	ByteOrderScope (const ByteOrderScope&)				= delete;
	ByteOrderScope& operator= (const ByteOrderScope&)	= delete;

private:
	DataStream&				ds;
	DataStream::ByteOrder	originalByteOrder; // #TODO replace with ::ByteOrder (then Types\DataStream.hpp can be replaced with KernelTypes.hpp)
};


template <typename T>
constexpr void FloatingPointTypeIsForbidden ()
{
	static_assert (
		!std::is_floating_point_v<T>,
		"This implementation does not support floating point types."
	);
}


template <typename T>
constexpr void CheckTypeForReadWrite ()
{
	static_assert (
		std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_enum_v<T>,
		"Only integral, floating point, and enum types are supported."
	);
}


KERNEL_EXPORT
void CheckStatus (const DataStream& ds);


template <typename T>
void ReadImpl (DataStream& ds, T& data)
{
	FloatingPointTypeIsForbidden<T> ();
	ds >> data;
}


template <> KERNEL_EXPORT void ReadImpl (DataStream& ds, float&  data);
template <> KERNEL_EXPORT void ReadImpl (DataStream& ds, double& data);


template <typename T>
size_t Read (DataStream& ds, T& data)
{
	CheckTypeForReadWrite<T> ();
	ReadImpl (ds, data);
	CheckStatus (ds);
	return sizeof (T);
}


template <typename T>
size_t Read (DataStream& ds, T& data, ByteOrder order)
{
	ByteOrderScope scope (ds, order);
	return Read (ds, data);
}


template <typename T>
void WriteImpl (DataStream& ds, const T& data)
{
	FloatingPointTypeIsForbidden<T> ();
	ds << data;
}


template <> KERNEL_EXPORT void WriteImpl (DataStream& ds, const float&  data);
template <> KERNEL_EXPORT void WriteImpl (DataStream& ds, const double& data);


template <typename T>
size_t Write (DataStream& ds, const T& data)
{
	CheckTypeForReadWrite<T> ();
	WriteImpl (ds, data);
	CheckStatus (ds);
	return sizeof (T);
}


template <typename T>
size_t Write (DataStream& ds, const T& data, ByteOrder order)
{
	ByteOrderScope scope (ds, order);
	return Write (ds, data);
}


#endif