#pragma once
#ifndef FileHandler__COFF_ObjectProcessor__hpp
#define FileHandler__COFF_ObjectProcessor__hpp

// #Standard
#include <functional>


namespace File {
namespace COFF {

class Object;
using ObjectProcessor = std::function<void (const Object&)>;

}
}


#endif