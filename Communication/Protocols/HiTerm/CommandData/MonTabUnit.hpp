#pragma once
#ifndef Communication__HiTerm_MonTabUnit__hpp
#define Communication__HiTerm_MonTabUnit__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Standard
#include <string>

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication::HiTerm {

enum MonTabUnit : UInt16 {
	Unit_None	= 0,
	Unit_A		= 1,
	Unit_V		= 2,
	Unit_kVA	= 3,
	Unit_kW		= 4,
	Unit_S		= 5,
	Unit_H		= 6,
	Unit_NM		= 7,
	Unit_kWh	= 8,
	Unit_Hz		= 9,
	Unit_Vs		= 10,
	Unit_NA		= 11,	// #TODO ???
	Unit_W		= 12,
	Unit_VAr	= 13,
	Unit_VA		= 14,
	Unit_RadPs	= 15,
	Unit_DI		= 16,	// #TODO ???
	Unit_Rad	= 17,
	Unit_VER	= 18,	// #TODO ???
	Unit_DEGC	= 19,	// #TODO ???
	Unit_PERC	= 20,	// #TODO ??? min ???
	Unit_BITF	= 21,	// #TODO ???
	Unit_100ms	= 22,
	Unit_ms		= 23,
	Unit_mA		= 24
};


COMMUNICATION_EXPORT
std::string ToString (MonTabUnit unit);

}


#endif