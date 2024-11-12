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

#ifndef _CORE_c_
    #define _CORE_c_

// Source files
#include "CORE/base.c"
#include "CORE/control.c"

#ifdef DEBUG_ALL
    #define BASE_DEBUG_ALL
    #define CONTROL_DEBUG_ALL
#endif // DEBUG_ALL

// Entry point
int main(int argc, char* argv)
{
    startTimeMillis = millis();
    startTimeMicros = micros();

    setup();
    while (1)
        loop();
}

#endif // _CORE_c_