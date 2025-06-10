#pragma once
#ifndef Communication__HiTerm_MessagePtr__hpp
#define Communication__HiTerm_MessagePtr__hpp

// #Standard
#include <memory>


namespace Communication::HiTerm {

class Message;
using MessagePtr = std::unique_ptr<Message>;

}


#endif