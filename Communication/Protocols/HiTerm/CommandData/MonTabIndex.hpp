#pragma once
#ifndef Communication__HiTerm_MonTabIndex__hpp
#define Communication__HiTerm_MonTabIndex__hpp

// #ExportHeader
#include "CommunicationExport.hpp"

// #Standard
#include <functional>

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication::HiTerm {

enum MonTabIndex : UInt8 {
	Tab0 = 0u,
	Tab1 = 1u,
	Tab2 = 2u,
	Tab3 = 3u,
	Tab4 = 4u,
	Tab5 = 5u,
	Tab6 = 6u,
	Tab7 = 7u,
	Tab8 = 8u,
	Tab9 = 9u,
};


void CheckTabIndex (MonTabIndex index);

COMMUNICATION_EXPORT
void EnumerateTabIndices (const std::function<void (MonTabIndex)>& enumerator);

}


#endif