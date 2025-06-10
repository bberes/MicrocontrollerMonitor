#pragma once
#ifndef Network__SerialPort_ErrorCode__hpp
#define Network__SerialPort_ErrorCode__hpp


namespace Network::SerialPort {

enum class ErrorCode {
	NoError,
	DeviceNotFound,
	Permission,
	UnsupportedOperation
};

}


#endif