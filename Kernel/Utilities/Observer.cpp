#include "Observer.hpp"

// #Kernel
#include "Types\Vector.hpp"


void Utilities::Subject::Attach (Observer& observer)
{
	Subject*& subject = observer.subject;
	if (subject == this) {
		return;
	}
	if (subject != nullptr) {
		subject->Detach (observer);
	}
	subject = this;
	observers.insert (&observer);
}


void Utilities::Subject::Detach (Observer& observer)
{
	if (observer.subject != this) {
		return;
	}
	observers.erase (&observer);
	observer.subject = nullptr;
}


Utilities::Subject::~Subject ()
{
	Vector<Observer*> toDetach;
	for (Observer* observer : observers) {
		toDetach.push_back (observer);
	}
	for (Observer* observer : toDetach) {
		Detach (*observer); // #Note: alters member `observers`, loop `toDetach` instead
	}
}


Utilities::Observer::~Observer ()
{
	if (subject == nullptr) {
		return;
	}
	subject->Detach (*this);
}