#include "ProcessorID.hpp"

// #Standard
#include <stdexcept>

// #Kernel
#include "Serialization\ReadWrite.hpp"


namespace {

constexpr UInt8 MASK_MSB = 0x80;


constexpr bool MaskMSB (UInt8 byte)
{
	return (byte & MASK_MSB) == MASK_MSB;
}

}


Communication::HiTerm::ProcessorID::ProcessorID (DeserializationSelector ds)
	: Deserializable (ds)
{
}


Communication::HiTerm::ProcessorID::ProcessorID (UInt8 id, DeviceRole role)
	: Deserializable	(RegularConstructor)
	, id				(id)
	, role				(role)
{
	if (MaskMSB (id)) {
		throw std::invalid_argument ("{E311D598-3EF1-4FFE-BF7E-6C69FD06A191}");
	}
}


size_t Communication::HiTerm::ProcessorID::Read (DataStream& is)
{
	const size_t size = ::Read (is, id);

	if (MaskMSB (id)) {
		role = DeviceRole::Slave;
		id ^= MASK_MSB;
	} else {
		role = DeviceRole::Master;
	}

	return size;
}


size_t Communication::HiTerm::ProcessorID::Write (DataStream& os) const
{
	UInt8 value = id;

	if (role == DeviceRole::Slave) {
		value |= MASK_MSB;
	}

	return ::Write (os, value);
}