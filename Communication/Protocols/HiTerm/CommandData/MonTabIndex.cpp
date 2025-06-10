#include "MonTabIndex.hpp"

// #Standard
#include <stdexcept>


void Communication::HiTerm::EnumerateTabIndices (const std::function<void (MonTabIndex)>& enumerator)
{
	for (UInt8 i = Tab0; i <= Tab9; ++i) {
		enumerator (static_cast<MonTabIndex> (i));
	}
}


void Communication::HiTerm::CheckTabIndex (MonTabIndex index)
{
	if (index > Tab9) {
		throw std::invalid_argument ("{C1B04894-402B-4CEF-9C46-27C8EC9FD01E}");
	}
}