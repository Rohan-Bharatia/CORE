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

#ifndef _CORE_CORE_c_
    #define _CORE_CORE_c_

// Source files
#include "src/prerequisites.c"
#include "src/string.cpp"
#include "src/serial.cpp"
#include "src/misc.cpp"
#include "src/time.cpp"
#include "src/io.cpp"
#include "src/interrupt.cpp"

// Entry point
int main(int argc, char* argv)
{
    startTimeMillis = millis();
    startTimeMicros = micros();

    setup();
    for (/* int i = 0 */; /* i < INFINITY */; /* ++i */)
        loop();
}

#endif // _CORE_CORE_c_