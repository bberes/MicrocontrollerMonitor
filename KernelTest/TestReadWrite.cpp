#include "pch.h"

// #Kernel
#include "Serialization\ReadWrite.hpp"
#include "Types\BaseTypes.hpp"
#include "Types\ByteArray.hpp"
#include "Types\DataStream.hpp"


namespace {

enum class Enum				{ Zero, Value = 0x01234567			};
enum class Enum1 : UInt8	{ Zero, Value = 0x89				};
enum class Enum2 : UInt16	{ Zero, Value = 0xABCD				};
enum class Enum4 : UInt32	{ Zero, Value = 0xEF012345			};
enum class Enum8 : UInt64	{ Zero, Value = 0x6789ABCDEF012345	};

}


TEST (TestReturnValueOfRead, WithUInt8)
{
	DataStream ds;
	UInt8 data = 0u;
	const size_t size = Read (ds, data);
	EXPECT_EQ (size, 1u);
}


TEST (TestReturnValueOfRead, WithUInt16)
{
	DataStream ds;
	UInt16 data = 0u;
	const size_t size = Read (ds, data);
	EXPECT_EQ (size, 2u);
}


TEST (TestReturnValueOfRead, WithUInt32)
{
	DataStream ds;
	UInt32 data = 0u;
	const size_t size = Read (ds, data);
	EXPECT_EQ (size, 4u);
}


TEST (TestReturnValueOfRead, WithUInt64)
{
	DataStream ds;
	UInt64 data = 0u;
	const size_t size = Read (ds, data);
	EXPECT_EQ (size, 8u);
}


TEST (TestReturnValueOfRead, WithFloat)
{
	DataStream ds;
	float data = 0.0f;
	const size_t size = Read (ds, data);
	EXPECT_EQ (size, 4u);
}


TEST (TestReturnValueOfRead, WithDouble)
{
	DataStream ds;
	double data = 0.0;
	const size_t size = Read (ds, data);
	EXPECT_EQ (size, 8u);
}


TEST (TestReturnValueOfRead, WithEnum)
{
	DataStream ds;
	Enum e {};
	const size_t size = Read (ds, e);
	EXPECT_EQ (size, sizeof (int));
	static_assert (sizeof (int) == 4u);
}


TEST (TestReturnValueOfRead, WithEnum1)
{
	DataStream ds;
	Enum1 e {};
	const size_t size = Read (ds, e);
	EXPECT_EQ (size, 1u);
}


TEST (TestReturnValueOfRead, WithEnum2)
{
	DataStream ds;
	Enum2 e {};
	const size_t size = Read (ds, e);
	EXPECT_EQ (size, 2u);
}


TEST (TestReturnValueOfRead, WithEnum4)
{
	DataStream ds;
	Enum4 e {};
	const size_t size = Read (ds, e);
	EXPECT_EQ (size, 4u);
}


TEST (TestReturnValueOfRead, WithEnum8)
{
	DataStream ds;
	Enum8 e {};
	const size_t size = Read (ds, e);
	EXPECT_EQ (size, 8u);
}


namespace {

class TestWrite : public ::testing::Test {
public:
	TestWrite ();

protected:
	ByteArray	writtenBytes;
	DataStream	ds;
};


TestWrite::TestWrite ()
	: ds (&writtenBytes, DataStream::OpenModeFlag::WriteOnly)
{
}

}


TEST_F (TestWrite, TestReturnValueWithUInt8)
{
	UInt8 data = 0u;
	const size_t size = Write (ds, data);
	EXPECT_EQ (size, 1u);
	EXPECT_EQ (size, writtenBytes.size ());
}


TEST_F (TestWrite, TestReturnValueWithUInt16)
{
	UInt16 data = 0u;
	const size_t size = Write (ds, data);
	EXPECT_EQ (size, 2u);
	EXPECT_EQ (size, writtenBytes.size ());
}


TEST_F (TestWrite, TestReturnValueWithUInt32)
{
	UInt32 data = 0u;
	const size_t size = Write (ds, data);
	EXPECT_EQ (size, 4u);
	EXPECT_EQ (size, writtenBytes.size ());
}


TEST_F (TestWrite, TestReturnValueWithUInt64)
{
	UInt64 data = 0u;
	const size_t size = Write (ds, data);
	EXPECT_EQ (size, 8u);
	EXPECT_EQ (size, writtenBytes.size ());
}


TEST_F (TestWrite, TestReturnValueWithFloat)
{
	float data = 0.0f;
	const size_t size = Write (ds, data);
	EXPECT_EQ (size, 4u);
	EXPECT_EQ (size, writtenBytes.size ());
}


TEST_F (TestWrite, TestReturnValueWithDouble)
{
	double data = 0.0;
	const size_t size = Write (ds, data);
	EXPECT_EQ (size, 8u);
	EXPECT_EQ (size, writtenBytes.size ());
}


TEST_F (TestWrite, TestReturnValueWithEnum)
{
	Enum e = Enum::Value;
	const size_t size = Write (ds, e);
	EXPECT_EQ (size, sizeof (int));
	EXPECT_EQ (size, writtenBytes.size ());
}


TEST_F (TestWrite, TestReturnValueWithEnum1)
{
	Enum1 e = Enum1::Value;
	const size_t size = Write (ds, e);
	EXPECT_EQ (size, 1u);
	EXPECT_EQ (size, writtenBytes.size ());
}


TEST_F (TestWrite, TestReturnValueWithEnum2)
{
	Enum2 e = Enum2::Value;
	const size_t size = Write (ds, e);
	EXPECT_EQ (size, 2u);
	EXPECT_EQ (size, writtenBytes.size ());
}


TEST_F (TestWrite, TestReturnValueWithEnum4)
{
	Enum4 e = Enum4::Value;
	const size_t size = Write (ds, e);
	EXPECT_EQ (size, 4u);
	EXPECT_EQ (size, writtenBytes.size ());
}


TEST_F (TestWrite, TestReturnValueWithEnum8)
{
	Enum8 e = Enum8::Value;
	const size_t size = Write (ds, e);
	EXPECT_EQ (size, 8u);
	EXPECT_EQ (size, writtenBytes.size ());
}


namespace {

class TestReadEnum : public ::testing::Test {
public:
	TestReadEnum ();

protected:
	ByteArray	bytes;
	DataStream	in;
};


TestReadEnum::TestReadEnum ()
	: in (&bytes, DataStream::OpenModeFlag::ReadOnly)
{
}

}


TEST_F (TestReadEnum, WithEnum)
{
	Enum e {};
	bytes.append ("\x01\x23\x45\x67");
	size_t size = Read (in, e);
	EXPECT_EQ (size, sizeof (int));
	EXPECT_EQ (e, Enum::Value);
}


TEST_F (TestReadEnum, WithEnum1)
{
	Enum1 e {};
	bytes.append ("\x89");
	size_t size = Read (in, e);
	EXPECT_EQ (size, 1u);
	EXPECT_EQ (e, Enum1::Value);
}


TEST_F (TestReadEnum, WithEnum2)
{
	Enum2 e {};
	bytes.append ("\xAB\xCD");
	size_t size = Read (in, e);
	EXPECT_EQ (size, 2u);
	EXPECT_EQ (e, Enum2::Value);
}


TEST_F (TestReadEnum, WithEnum4)
{
	Enum4 e {};
	bytes.append ("\xEF\x01\x23\x45");
	size_t size = Read (in, e);
	EXPECT_EQ (size, 4u);
	EXPECT_EQ (e, Enum4::Value);
}


TEST_F (TestReadEnum, WithEnum8)
{
	Enum8 e {};
	bytes.append ("\x67\x89\xAB\xCD\xEF\x01\x23\x45");
	size_t size = Read (in, e);
	EXPECT_EQ (size, 8u);
	EXPECT_EQ (e, Enum8::Value);
}