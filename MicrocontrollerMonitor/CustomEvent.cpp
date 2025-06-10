#include "CustomEvent.hpp"


CustomEvent::CustomEvent (const std::function<void ()>& process)
	: QEvent	(QEvent::Type::User)
	, process	(process)
{
}


CustomEvent::~CustomEvent ()
{
}


void CustomEvent::Process ()
{
	process ();
}


CustomEvent* CustomEvent::clone () const
{
	return new CustomEvent (*this);
}