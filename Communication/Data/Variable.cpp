#include "Variable.hpp"

// #Standard
#include <stdexcept>


void Communication::Variable::CheckVariableSize (size_t size) const
{
	if (static_cast<size_t> (info.GetVariableSize ()) != size) {
		throw std::invalid_argument ("{08950AA0-BAC9-446F-B394-9CE92CA12C2D}");
	}
}