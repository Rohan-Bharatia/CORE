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
    #define DEBUG_ROTATION
#elif VRC_DEBUG_NONE
    #undef DEBUG_DRIVER
    #undef DEBUG_SMART_MOTOR
    #undef DEBUG_ROTATION
#endif // VRC_DEBUG_ALL

// Motor commands
#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

// Motor commands
#define MOTOR_SPEED_SET 0x10 // TODO: Fix code, this is a placeholder code
#define MOTOR_SPEED_GET 0x11 // TODO: Fix code, this is a placeholder code
#define MOTOR_MOVE      0x20 // TODO: Fix code, this is a placeholder code
#define MOTOR_STOP      0x30 // TODO: Fix code, this is a placeholder code

// Rotation commands
#define ROTATION_POSITION_SET 0x40 // TODO: Fix code, this is a placeholder code
#define ROTATION_POSITION_GET 0x41 // TODO: Fix code, this is a placeholder code
#define ROTATION_ANGLE_SET    0x40 // TODO: Fix code, this is a placeholder code
#define ROTATION_ANGLE_GET    0x41 // TODO: Fix code, this is a placeholder code
#define ROTATION_VELOCITY_SET 0x50 // TODO: Fix code, this is a placeholder code
#define ROTATION_VELOCITY_GET 0x51 // TODO: Fix code, this is a placeholder code
#define ROTATION_RESET        0x60 // TODO: Fix code, this is a placeholder code

#endif // _VRC_PREREQUISITES_c_