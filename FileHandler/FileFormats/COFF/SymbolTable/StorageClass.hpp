#pragma once
#ifndef FileHandler__COFF_StorageClass__hpp
#define FileHandler__COFF_StorageClass__hpp

// #Kernel
#include "Types\BaseTypes.hpp"


enum class StorageClass : UInt8 {
	C_NULL		= 0,	// No storage class
	C_AUTO		= 1,	// Reserved
	C_EXT		= 2,	// External definition
	C_STAT		= 3,	// Static
	C_REG		= 4,	// Reserved
	C_EXTREF	= 5,	// External reference
	C_LABEL		= 6,	// Label
	C_ULABEL	= 7,	// Undefined label
	C_MOS		= 8,	// Reserved
	C_ARG		= 9,	// Reserved
	C_STRTAG	= 10,	// Reserved
	C_MOU		= 11,	// Reserved
	C_UNTAG		= 12,	// Reserved
	C_TPDEF		= 13,	// Reserved
	C_USTATIC	= 14,	// Undefined static
	C_ENTAG		= 15,	// Reserved
	C_MOE		= 16,	// Reserved
	C_REGPARM	= 17,	// Reserved
	C_FIELD		= 18,	// Reserved
	C_UEXT		= 19,	// Tentative external definition
	C_STATLAB	= 20,	// Static load time label
	C_EXTLAB	= 21,	// External load time label
	C_VARARG	= 27,	// Last declared parameter of a function with a variable number of arguments
	C_BLOCK		= 100,	// Reserved
	C_FCN		= 101,	// Reserved
	C_EOS		= 102,	// Reserved
	C_FILE		= 103,	// Reserved	C_LINE		= 104	// Used only by utility programs
};


#endif