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

#ifndef _ALGORITHM_PREREQUISITES_c_
    #define _ALGORITHM_PREREQUISITES_c_

#ifdef ALGORITHM_DEBUG_ALL
    #define DEBUG_BEZIER
    #define DEBUG_TRAJECTORY
    #define DEBUG_A_STAR
    #define DEBUG_DRIVETRAIN
#elif ALGORITHM_DEBUG_NONE
    #undef DEBUG_BEZIER
    #undef DEBUG_TRAJECTORY
    #undef DEBUG_A_STAR
    #undef DEBUG_DRIVETRAIN
#endif // ALGORITHM_DEBUG_ALL

#endif // _ALGORITHM_PREREQUISITES_c_