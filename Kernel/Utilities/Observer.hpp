#pragma once
#ifndef Kernel__Utilities_Observer__hpp
#define Kernel__Utilities_Observer__hpp

// #ExportHeader
#include "KernelExport.hpp"

// #Standard
#include <unordered_set>


namespace Utilities {

class Observer;


class KERNEL_EXPORT Subject {
public:
	Subject (Subject&&)					= delete;
	Subject (const Subject&)			= delete;
	Subject& operator= (Subject&&)		= delete;
	Subject& operator= (const Subject&)	= delete;

	void Attach (Observer& observer);
	void Detach (Observer& observer);

protected:
	Subject () = default;
	~Subject ();

	using Observers = std::unordered_set<Observer*>;
	const Observers& GetObservers () const { return observers; }

private:
	Observers observers;
};


class KERNEL_EXPORT Observer {
public:
	Observer (Observer&&)					= delete; // for simplicity
	Observer (const Observer&)				= delete; // for simplicity
	Observer& operator= (Observer&&)		= delete; // for simplicity
	Observer& operator= (const Observer&)	= delete; // for simplicity

protected:
	Observer () = default;
	~Observer ();

private:
	friend Subject;
	Subject* subject = nullptr;
};

}


#endif