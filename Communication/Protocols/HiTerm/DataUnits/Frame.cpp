#include "Frame.hpp"

// #Kernel
#include "Utilities\Debug.hpp"

// #Communication
#include "Protocols\HiTerm\Utilities\Codec.hpp"
#include "Protocols\HiTerm\Utilities\FrameIDs.hpp"
#include "Packet.hpp"


Communication::HiTerm::Frame::Frame (const Packet& packet)
{
	frame.append (FrameID::STX);
	frame.append (Encode (packet));
	frame.append (FrameID::ETX);
}


static void CheckFrame (const ByteArray& frame)
{
	constexpr size_t MinLength =
		+ sizeof (UInt8)	// STX
		+ sizeof (UInt8)	// ucID
		+ sizeof (UInt8)	// cmdID
		+ sizeof (UInt8)	// Key
		+ sizeof (UInt16)	// Length
		+ 0u				// Data
		+ sizeof (UInt16)	// CRC
		+ sizeof (UInt8)	// ETX
		;

	if (frame.size () < MinLength) {
		TODO; // #TODO_ExceptionHandling
	}

	using namespace Communication::HiTerm::FrameID;
	if (frame.front () != STX) {
		TODO;
	}
	if (frame.back () != ETX) {
		TODO;
	}

	auto b = frame.begin ();
	auto e = frame.end ();
	for (++b, --e; b != e; ++b) {
		if (STX == *b || ETX == *b) {
			TODO;
		}
	}
}


Communication::HiTerm::Frame::Frame (ByteArray&& byteStream)
	: frame (byteStream)
{
	CheckFrame (frame); // STX, ETX, min length
}


Communication::HiTerm::Frame::Frame (const ByteArray& byteStream)
	: frame (byteStream)
{
	CheckFrame (frame);
}


Communication::HiTerm::Frame::operator Communication::HiTerm::Packet () const
{
	auto b = frame.begin ();
	auto e = frame.end ();

	ByteArray encodedData;
	for (++b, --e; b != e; ++b) {
		encodedData.append (*b);
	}

	return Packet (Decode (encodedData));
}


Communication::HiTerm::Frame::operator const ByteArray& () const
{
	return frame;
}