#include "pch.h"

// #Kernel
#include "Types\ByteArray.hpp"

// #Communication
#include "Protocols\HiTerm\Utilities\Codec.hpp"
#include "Protocols\HiTerm\Utilities\FrameIDs.hpp"


using namespace Communication::HiTerm;


static ByteArray GetCustomByteArray (std::initializer_list<uint8_t> list)
{
	ByteArray byteArray;
	for (auto& elem : list) {
		byteArray.append (elem);
	}
	return byteArray;
}


TEST (TestEncode, WithBytes_STX)
{
	const auto& bytes = GetCustomByteArray ({ FrameID::STX });
	const auto& result = Encode (bytes);
	const auto& expected = GetCustomByteArray ({ FrameID::DLE, FrameID::XDAT ^ FrameID::STX });

	EXPECT_EQ (result, expected);
}


TEST (TestDecode, DISABLED_WithBytes_STX)
{
	const auto& bytes = GetCustomByteArray ({ FrameID::STX });
	const auto& result = Decode (bytes);
	const auto& expected = bytes;

	EXPECT_EQ (result, expected);
}