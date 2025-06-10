#include "pch.h"

// #Kernel
#include "Types\ByteArray.hpp"
#include "Utilities\CRC.hpp"


static ByteArray GetCustomByteArray (std::initializer_list<uint8_t> list)
{
	ByteArray byteArray;
	for (auto& elem : list) {
		byteArray.append (elem);
	}
	return byteArray;
}


TEST (TestFastCRC16, WithTheseBytes0x0207)
{
	const auto& byteArray = GetCustomByteArray ({ 0x02, 0x07 });
	const UInt16 crc = Utilities::FastCRC16 (byteArray);

	EXPECT_EQ (crc, 0x1241);
}


TEST (TestCalcCRC16, WithTheseBytes0x0207)
{
	const auto& byteArray = GetCustomByteArray ({ 0x02, 0x07 });
	const UInt16 crc = Utilities::CalcCRC16 (byteArray);

	EXPECT_EQ (crc, 0x1241);
}