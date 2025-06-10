#include "RecorderTypes.hpp"

// #Communication
#include "Data\Variable.hpp"


StateListener::StateListener (const Communication::MemoryRef& mr)
	: mr (mr)
{
}


void StateListener::Update (const Communication::Variables& variables)
{
	if (variables.size () != 1u || variables[0u].GetInfo () != mr) {
		return; // #ToDo: log ???
	}

	const auto value = variables[0u].GetValue<UInt16> ();
	const bool ready = value == 0x00 || value == 0x03; // #ToDo: resolve these magic numbers
	emit StateReceived (ready);
}


void WriteListener::Update ()
{
	emit WriteFinished ();
}


void ParamsListener::Update (const Communication::Variables& variables)
{
	if (refs.size () != variables.size ()) {
		return; // ToDo: log ?
	}

	for (size_t i = 0u; i < refs.size (); ++i) {
		if (refs[i] != variables[i].GetInfo ()) {
			return; // ToDo: log ?
		}
	}

	emit ParamsReceived ();
}


void ArrayListener::Init ()
{
	data.clear ();
	iter = 0u;
	addr = StartAddr;
	len  = LengthUnit;
}


void ArrayListener::Update (const std::vector<UInt32>& variables)
{
	++iter;

	for (auto& v : variables) {
		data.push_back (v);
	}

	emit DataReceived ();
}