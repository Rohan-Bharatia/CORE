#pragma region LICENSE

//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
// 
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//                               ...
//                  Copyright (C) 2024 Rohan Bharatia

#pragma endregion LICENSE

#pragma once

#ifndef _BASE_TIME_cpp_
    #define _BASE_TIME_cpp_

#include <chrono>
#include <thread>

#include "prerequisites.c"

inline void delay(const unsigned long milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
inline void delayMicroseconds(const unsigned long microseconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
}

unsigned long micros(void)
{
    double duration = std::chrono::system_clock::now().time_since_epoch();
    return (unsigned long)std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() - startTimeMillis;
}
unsigned long millis(void)
{
    double duration = std::chrono::system_clock::now().time_since_epoch();
    return (unsigned long)std::chrono::duration_cast<std::chrono::microseconds>(duration).count() - startTimeMicros;
}

#endif // _BASE_TIME_cpp_