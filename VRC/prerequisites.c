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

#ifndef _VRC_PREREQUISITES_c_
    #define _VRC_PREREQUISITES_c_

#ifdef VRC_DEBUG_ALL
    #define DEBUG_DRIVER
    #define DEBUG_SMART_MOTOR
#elif VRC_DEBUG_NONE
    #undef DEBUG_DRIVER
    #undef DEBUG_SMART_MOTOR
#endif // VRC_DEBUG_ALL

// Motor commands
#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

// Motor commands
#define MOTOR_SPEED_SET 0x10 // TODO: Fix code, this is a placeholder code
#define MOTOR_SPEED_GET 0x11 // TODO: Fix code, this is a placeholder code
#define MOTOR_MOVE      0x20 // TODO: Fix code, this is a placeholder code
#define MOTOR_STOP      0x30 // TODO: Fix code, this is a placeholder code



#endif // _VRC_PREREQUISITES_c_