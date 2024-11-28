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
#include "CORE/subsystem.c"
#include "CORE/algorithm.c"

#undef EMERGENCY_QUIT

#ifdef DEBUG_ALL
    #define BASE_DEBUG_ALL
    #define CONTROL_DEBUG_ALL
    #define SUBSYSTEM_DEBUG_ALL
    #define ALGORITHM_DEBUG_ALL
#elif DEBUG_NONE
    #define BASE_DEBUG_NONE
    #define CONTROL_DEBUG_NONE
    #define SUBSYSTEM_DEBUG_NONE
    #define ALGORITHM_DEBUG_NONE
#endif // DEBUG_ALL

void emergencyStop(void)
{
    #define EMERGENCY_QUIT
}

// Entry point
int main(int argc, char* argv)
{
    startTimeMillis = millis(void);
    startTimeMicros = micros(void);

    setup(void);
    while (1)
    {
        loop(void);
    #ifdef EMERGENCY_QUIT
        return 1;
    #endif // EMERGENCY_QUIT
    }
}

#endif // _CORE_c_