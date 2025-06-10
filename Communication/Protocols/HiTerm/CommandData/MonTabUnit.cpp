#include "MonTabUnit.hpp"

// #Standard
#include <stdexcept>


static_assert (sizeof (Communication::HiTerm::MonTabUnit) == 2u, "MonTabUnit must be 2-byte-length!");


std::string Communication::HiTerm::ToString (MonTabUnit unit)
{
	switch (unit) {
	case Communication::HiTerm::Unit_None:	return "None";
	case Communication::HiTerm::Unit_A:		return "A";
	case Communication::HiTerm::Unit_V:		return "V";
	case Communication::HiTerm::Unit_kVA:	return "kVA";
	case Communication::HiTerm::Unit_kW:	return "kW";
	case Communication::HiTerm::Unit_S:		return "S";
	case Communication::HiTerm::Unit_H:		return "H";
	case Communication::HiTerm::Unit_NM:	return "NM";
	case Communication::HiTerm::Unit_kWh:	return "kWh";
	case Communication::HiTerm::Unit_Hz:	return "Hz";
	case Communication::HiTerm::Unit_Vs:	return "Vs";
	case Communication::HiTerm::Unit_NA:	return "NA";	// #TODO ???
	case Communication::HiTerm::Unit_W:		return "W";
	case Communication::HiTerm::Unit_VAr:	return "VAr";
	case Communication::HiTerm::Unit_VA:	return "VA";
	case Communication::HiTerm::Unit_RadPs:	return "RAD/s";
	case Communication::HiTerm::Unit_DI:	return "DI";	// #TODO ???
	case Communication::HiTerm::Unit_Rad:	return "Rad";
	case Communication::HiTerm::Unit_VER:	return "VER";	// #TODO ???
	case Communication::HiTerm::Unit_DEGC:	return "DEGC";	// #TODO ???
	case Communication::HiTerm::Unit_PERC:	return "PERC";	// #TODO ??? min ???
	case Communication::HiTerm::Unit_BITF:	return "BITF";	// #TODO ???
	case Communication::HiTerm::Unit_100ms:	return "100 ms";
	case Communication::HiTerm::Unit_ms:	return "ms";
	case Communication::HiTerm::Unit_mA:	return "mA";
	}
    throw std::invalid_argument ("{D4BB61FB-E641-48A9-A913-360E8E8499CD}");
}