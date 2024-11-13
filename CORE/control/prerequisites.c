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

#ifndef _CONTROL_PREREQUISITES_c_
    #define _CONTROL_PREREQUISITES_c_

#ifdef CONTROL_DEBUG_ALL
    #define DEBUG_PID
    #define DEBUG_FAULT
    #define DEBUG_BEZIER
    #define DEBUG_SIGNAL_CONDITION
    #define DEBUG_ESTIMATION
    #define DEBUG_TRAJECTORY
    #define DEBUG_FEED_FORWARD
    #define DEBUG_STATE_SPACE
    #define DEBUG_MODEL_PREDICTIVE
    #define DEBUG_LIMITER
    #define DEBUG_HEALTH
#endif // CONTROL_DEBUG_ALL

#endif // _CONTROL_PREREQUISITES_c_