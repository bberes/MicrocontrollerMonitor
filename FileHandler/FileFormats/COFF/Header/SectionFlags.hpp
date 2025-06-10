#pragma once
#ifndef FileHandler__COFF_SectionFlags__hpp
#define FileHandler__COFF_SectionFlags__hpp

// #Kernel
#include "Types\BaseTypes.hpp"


enum class SectionFlags : UInt32 {
	STYP_REG	= 0x00000000u,	// Regular section (allocated, relocated, loaded)
	STYP_DSECT	= 0x00000001u,	// Dummy section (relocated, not allocated, not loaded)
	STYP_NOLOAD	= 0x00000002u,	// Noload section (allocated, relocated, not loaded)
	STYP_GROUP	= 0x00000004u,	// Grouped section (formed from several input sections). Other devices: Reserved
	STYP_PAD	= 0x00000008u,	// Padding section (loaded, not allocated, not relocated). Other devices: Reserved
	STYP_COPY	= 0x00000010u,	// Copy section (relocated, loaded, but not allocated; relocation entries are processed normally)
	STYP_TEXT	= 0x00000020u,	// Section contains executable code
	STYP_DATA	= 0x00000040u,	// Section contains initialized data
	STYP_BSS	= 0x00000080u,	// Section contains uninitialized data
	STYP_BLOCK	= 0x00001000u,	// Alignment used as a blocking factor.
	STYP_PASS	= 0x00002000u,	// Section should pass through unchanged.
	STYP_CLINK	= 0x00004000u,	// Section requires conditional linking
	STYP_VECTOR	= 0x00008000u,	// Section contains vector table.
	STYP_PADDED	= 0x00010000u	// Section has been padded.
};


#endif