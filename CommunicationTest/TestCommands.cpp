#include "pch.h"

// #Kernel
#include "Types\ByteArray.hpp"
#include "Types\DataStream.hpp"

// #Communication
#include "Protocols\HiTerm\Commands\Ping.hpp"
#include "Protocols\HiTerm\Commands\ReadBlackboxContent.hpp"
#include "Protocols\HiTerm\Commands\ReadBlackboxContent_DEPRECATED.hpp"
#include "Protocols\HiTerm\Commands\ReadMonTab.hpp"
#include "Protocols\HiTerm\Commands\ReadTabNames.hpp"
#include "Protocols\HiTerm\Commands\ReadTabValues.hpp"
#include "Protocols\HiTerm\Commands\ReadUnits.hpp"
#include "Protocols\HiTerm\Commands\ReadVariables.hpp"
#include "Protocols\HiTerm\Commands\ReadVariables_DEPRECATED.hpp"
#include "Protocols\HiTerm\Commands\Reboot.hpp"
#include "Protocols\HiTerm\Commands\WriteVariables.hpp"
#include "Protocols\HiTerm\Utilities\ProcessorID.hpp"


using namespace Communication::HiTerm;


namespace {

constexpr UInt8 ByteX12 = 0x12;
constexpr UInt8 ByteX34 = 0x34;


class TestCommand : public ::testing::Test {
protected:
	TestCommand ();

	template <typename Type, typename... Args>
	void Run (const Args& ...args);

private:
	virtual void TearDown () override final;

private:
	const UInt8	key;
	ByteArray	writtenBytes;
	DataStream	os;
	bool		hasRun;
};


TestCommand::TestCommand ()
	: key			(ByteX34)
	, writtenBytes	()
	, os			(&writtenBytes, DataStream::OpenModeFlag::WriteOnly)
	, hasRun		(false)
{
}


template <typename Type, typename... Args>
void TestCommand::Run (const Args& ...args)
{
	Type message (key, args...);
	const size_t size = message.Write (os);

	DataStream is (writtenBytes);
	Type rMessage (ForDeserialization);
	const size_t rSize = rMessage.Read (is);
	EXPECT_EQ (size, rSize);

	const UInt8 rKey = rMessage.GetKey ();
	EXPECT_EQ (key, rKey);

//	expect (rMessage); // #TODO_AdditionalExpectations
	hasRun = true;
}


void TestCommand::TearDown ()
{
	EXPECT_EQ (hasRun, true);
}

}


TEST_F (TestCommand, Serialization_Ping_Command)
{
	Run<Ping::Command> ();
}


TEST_F (TestCommand, Serialization_Ping_Response)
{
	Ping::Response::Status status = Ping::Response::FlashApiRun;
	Run<Ping::Response> (status);
	// #TODO
}


TEST_F (TestCommand, Serialization_ReadBlackboxContent_Command)
{
	UInt32 address	= 0u;
	UInt16 length	= 0u;
	BlackboxContent::Info info (address, length);
	Run<ReadBlackboxContent::Command> (info);
	// #TODO
}


TEST_F (TestCommand, Serialization_ReadBlackboxContent_Response)
{
	UInt32 address = 0u;
	BlackboxContent::Content content;
	BlackboxContent blackboxContent (address, content);
	Run<ReadBlackboxContent::Response> (blackboxContent);
	// #TODO
}


TEST_F (TestCommand, Serialization_Deprecated_ReadBlackboxContent_Command)
{
	UInt32 address	= 0u;
	UInt16 length	= 0u;
	BlackboxContent::Info info (address, length);
	Run<Deprecated::ReadBlackboxContent::Command> (info);
	// #TODO
}


TEST_F (TestCommand, Serialization_Deprecated_ReadBlackboxContent_Response)
{
	UInt32 address	= 0u;
	UInt16 length	= 0u;
	BlackboxContent::Info info (address, length);
	BlackboxContent::Content content;
	Deprecated::BlackboxContent blackboxContent (info, content);
	Run<Deprecated::ReadBlackboxContent::Response> (blackboxContent);
	// #TODO
}


TEST_F (TestCommand, Serialization_ReadMonTab_Command)
{
	MonTabIndex index = Tab5;
	Run<ReadMonTab::Command> (index);
}


TEST_F (TestCommand, Serialization_ReadMonTab_Response)
{
	MonTabIndex index = Tab5;
	MonTab monTab;
	Run<ReadMonTab::Response> (index, monTab);
	// #TODO
}


TEST_F (TestCommand, Serialization_ReadTabNames_Command)
{
	Run<ReadTabNames::Command> ();
}


TEST_F (TestCommand, Serialization_ReadTabNames_Response)
{
	std::string name;
	Run<ReadTabNames::Response> (name);
	// #TODO
}


TEST_F (TestCommand, Serialization_ReadTabValues_Command)
{
	MonTabIndex index = Tab5;
	Run<ReadTabValues::Command> (index);
}


TEST_F (TestCommand, Serialization_ReadTabValues_Response)
{
	MonTabIndex index = Tab5;
	Values values;
	Run<ReadTabValues::Response> (index, values);
	// #TODO
}


TEST_F (TestCommand, Serialization_ReadUnits_Command)
{
	Run<ReadUnits::Command> ();
}


TEST_F (TestCommand, Serialization_ReadUnits_Response)
{
	ByteArray units;
	Run<ReadUnits::Response> (units);
	// #TODO
}


TEST_F (TestCommand, Serialization_ReadVariables_Command)
{
	MemoryEntries entries;
	Run<ReadVariables::Command> (entries);
	// #TODO
}


TEST_F (TestCommand, Serialization_ReadVariables_Response)
{
	Variables variables;
	Run<ReadVariables::Response> (variables);
	// #TODO
}


TEST_F (TestCommand, Serialization_Deprecated_ReadVariables_Command)
{
//	MemoryEntries entries;
//	Run<Deprecated::ReadVariables::Command> (entries);
	// #TODO
}


TEST_F (TestCommand, Serialization_Deprecated_ReadVariables_Response)
{
//	Variables variables;
//	Run<Deprecated::ReadVariables::Response> (variables);
	// #TODO
}


TEST_F (TestCommand, Serialization_Reboot_Command)
{
	Run<Reboot::Command> ();
}


TEST_F (TestCommand, Serialization_Reboot_Response)
{
	Run<Reboot::Response> ();
}


TEST_F (TestCommand, Serialization_WriteVariables_Command)
{
	Variables variables;
	Run<WriteVariables::Command> (variables);
	// #TODO
}


TEST_F (TestCommand, Serialization_WriteVariables_Response)
{
	Run<WriteVariables::Response> ();
}