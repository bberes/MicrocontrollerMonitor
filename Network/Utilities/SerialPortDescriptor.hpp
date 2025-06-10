#pragma once
#ifndef Network__SerialPort_Descriptor__hpp
#define Network__SerialPort_Descriptor__hpp

// #Standard
#include <string>

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Network::SerialPort {

enum BaudRate : Int32 {
	BR_1200		=   1200,
	BR_2400		=   2400,
	BR_4800		=   4800,
	BR_9600		=   9600,
	BR_19200	=  19200,
	BR_38400	=  38400,
	BR_57600	=  57600,
	BR_115200	= 115200
};

enum class DataBits {
	DB_5 = 5,
	DB_6 = 6,
	DB_7 = 7,
	DB_8 = 8
};

enum class Parity {
	No,
	Even,
	Odd,
	Space,
	Mark
};

enum class StopBits {
	One,
	OneAndHalf,
	Two
};

enum class FlowControl {
	No,
	Hardware,
	Software
};


class Descriptor final {
public:
	std::string				portName;
	Int32					baudRate;
	SerialPort::DataBits	dataBits;
	SerialPort::StopBits	stopBits;
	SerialPort::Parity		parity;
	SerialPort::FlowControl	flowControl;
};

}


#endif