#pragma once
#ifndef Kernel__KernelTypes__hpp
#define Kernel__KernelTypes__hpp


class QByteArray;
class QDataStream;

using ByteArray		= QByteArray;
using DataStream	= QDataStream;


namespace Utilities {
	class Logger;
	class LoggerProxy;
}


#endif