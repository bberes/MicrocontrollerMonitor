#include "Codec.hpp"

// #Kernel
#include "Types\ByteArray.hpp"
#include "Utilities\Debug.hpp"

// #Communication
#include "FrameIDs.hpp"


namespace {

using namespace Communication::HiTerm;


// Encode (-->) / Decode (<--) bytes
// STX -> DLE (STX ^ XDAT)
// ETX -> DLE (ETX ^ XDAT)
// DLE -> DLE (DLE ^ XDAT)


void Encode (ByteArray& result, UInt8 byte)
{
	switch (byte) {
	case FrameID::STX:
	case FrameID::ETX:
	case FrameID::DLE:
		result.append (FrameID::DLE).append (byte ^ FrameID::XDAT);
		break;
	default:
		result.append (byte);
	}
}


void Decode (ByteArray& result, const ByteArray& source, ByteArray::ConstIterator& sourceIt)
{
	if (FrameID::DLE == *sourceIt) {
		if (++sourceIt == source.end ()) {
			TODO; // #TODO_ExceptionHandling
		}
		result.append (*sourceIt ^ FrameID::XDAT);
	} else {
		result.append (*sourceIt);
	}
}

}


ByteArray Communication::HiTerm::Encode (const ByteArray& source)
{
	ByteArray result;
	for (auto& byte : source) {
		::Encode (result, byte);
	}
	return result;
}


ByteArray Communication::HiTerm::Decode (const ByteArray& source)
{
	ByteArray result;
	for (auto it = source.begin (); it != source.end (); ++it) {
		::Decode (result, source, it);
	}
	return result;
}


// Packet
// +-----+---------+---------+-----+--------+------+-----+-----+
// | STX | Address | Command | Key | Length | Data | CRC | ETX |
// +-----+---------+---------+-----+--------+------+-----+-----+
//  STX     - 1 Byte, start sign
//  Address - 1 Byte, address of DSP 0-127, MSB is 0 by Master and 1 by Slave
//  Command - 1 Byte, defines the action between the DSP and the PC
//  Key     - 1 Byte, slave should send the answer with same Key
//  Length  - 2 Bytes, Length of the Data field, MSBF
//  Data    - defined for different commands
//  CRC     - 2 Bytes, LSBF, calculation method:
//				https://modbus.org/docs/Modbus_over_serial_line_V1_02.pdf page 39.
//  ETX     - 1 Byte, end sign
//
// +--------------------------------------------------------------------------+
// |                                                                          |
// | The rethought data structure based on the analogy with the TCP/IP Model  |
// |                                                                          |
// +--------------------------------------------------------------------------+
// |                                                                          |
// |   Layer Name                          Structure                          |
// |                                                                          |
// |                +------------------------------------------------------+  |
// | Network Access |                        Frame                         |  |
// |                +-----+------------------------------------------------+  |
// | Internet       | STX |                  Packet                  | ETX |  |
// |                +-----+------+-------+-----+--------+------+-----+-----+  |
// | Transport      | STX | ucID | cmdID |       Message       | CRC | ETX |  |
// |                +-----+------+-------+-----+--------+------+-----+-----+  |
// | Application    | STX | ucID | cmdID | Key | Length | Data | CRC | ETX |  |
// |                +-----+------+-------+-----+--------+------+-----+-----+  |
// |                                                                          |
// | Between the PC and the microcontroller (uc) the sent and received bytes  |
// | form a Frame.                                                            |
// |                                                                          |
// | Each Frame consists of 3 parts:                                          |
// |  - STX (Frame starting sign),                                            |
// |  - Encoded Data (free from special signs: STX and ETX),                  |
// |  - ETX (Frame ending sign).                                              |
// |                                                                          |
// | The Encoded Data represents a Packet, the result of the decoding process |
// | is the Decoded Data which is a Packet.                                   |
// |                                                                          |
// | Each Packet consists of 4 parts:                                         |
// |  - ID of the microcontroller, ucID (also referred as Address),           |
// |  - ID of the Command, cmdID (also referred as Command),                  |
// |  - real Command (more appropriate to call as Message),                   |
// |  - CRC data of the above 3 parts.                                        |
// |                                                                          |
// | Finally the Message consists of 3 parts:                                 |
// |  - Key,                                                                  |
// |  - Length of the Data part,                                              |
// |  - Data.                                                                 |
// |                                                                          |
// | The Application handles the ucID, cmdID, Key and Data parts.             |
// |                                                                          |
// +--------------------------------------------------------------------------+