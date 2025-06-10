#include "Variable.hpp"

// #Standard
#include <stdexcept>


Utilities::IVariable::~IVariable () = default;


namespace {

std::string ToHEX (const UInt8 n)
{
	if (n < 10u) {
		return std::to_string (n);
	}
	switch (n) {
	case 10u:	return "A";
	case 11u:	return "B";
	case 12u:	return "C";
	case 13u:	return "D";
	case 14u:	return "E";
	case 15u:	return "F";
	}
	throw std::invalid_argument ("{4507C0E9-CC84-411F-AC01-D85F191B56F5}");
}

}


std::string Utilities::ByteToHEX (const UInt8 byte)
{
	std::string result;
	result += ToHEX (byte / 16u);
	result += ToHEX (byte % 16u);
	return result;
}