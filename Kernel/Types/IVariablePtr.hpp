#pragma once
#ifndef Kernel__Utilities_IVariablePtr__hpp
#define Kernel__Utilities_IVariablePtr__hpp

// #Standard
#include <memory>


namespace Utilities {

class IVariable;
using IVariablePtr = std::unique_ptr<IVariable>;

}


#endif