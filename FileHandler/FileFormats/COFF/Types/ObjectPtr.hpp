// #ToDo: remove this file, use Owner<Object> instead !!!
#pragma once
#ifndef FileHandler__COFF_ObjectPtr__hpp
#define FileHandler__COFF_ObjectPtr__hpp

// #Standard
#include <memory>


namespace File {
namespace COFF {

class Object;

using ObjectPtr			= std::unique_ptr<Object>;
using ObjectConstPtr	= std::unique_ptr<const Object>;

}
}


#endif