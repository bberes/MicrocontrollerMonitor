#pragma once
#ifndef MM__Utilities__hpp
#define MM__Utilities__hpp

// #MicrocontrollerMonitor
#include "MicrocontrollerMonitorTypes.hpp"


// #Note: dtor of parent handles deletion
template <class DerivedClass>
DerivedClass* MakeChild (QWidget& parent)
{
	static_assert (std::is_base_of_v<QObject, DerivedClass>, "DerivedClass must be derived from QObject!");
	return new DerivedClass (&parent);
}


// #Note: creates event for fn. QCoreApplication::postEvent that takes ownership
template <class EventClass, typename... Args>
EventClass* MakeEvent (Args&&... args)
{
	static_assert (std::is_base_of_v<QEvent, EventClass>, "EventClass must be derived from QEvent!");
	return new EventClass (std::forward<Args> (args)...);
}


#endif