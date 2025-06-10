#pragma once
#ifndef Communication__HiTerm_MessageProcessorPtr__hpp
#define Communication__HiTerm_MessageProcessorPtr__hpp

// #Standard
#include <memory>


namespace Communication::HiTerm {

class MessageProcessor;
using MessageProcessorPtr = std::unique_ptr<MessageProcessor>;

}


#endif