#pragma once
#ifndef Kernel__DataStreamStatus__hpp
#define Kernel__DataStreamStatus__hpp


enum class DataStreamStatus {
    Ok,
    ReadPastEnd,
    ReadCorruptData,
    WriteFailed
};


#endif