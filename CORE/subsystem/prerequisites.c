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

#ifndef _SUBSYSTEM_PREREQUISITES_c_
    #define _SUBSYSTEM_PREREQUISITES_c_

#define LEFT -1
#define RIGHT 1

#ifdef SUBSYSTEM_DEBUG_ALL
    #define DEBUG_MOTOR
    #define DEBUG_IMU
    #define DEBUG_THERMAL
    #define DEBUG_HUMIDITY
    #define DEBUG_PRESSURE
    #define DEBUG_ULTRASONIC
#elif SUBSYSTEM_DEBUG_NONE
    #undef DEBUG_MOTOR
    #undef DEBUG_IMU
    #undef DEBUG_THERMAL
    #undef DEBUG_HUMIDITY
    #undef DEBUG_PRESSURE
    #undef DEBUG_ULTRASONIC
#endif // SUBSYSTEM_DEBUG_ALL

#endif // _SUBSYSTEM_PREREQUISITES_c_