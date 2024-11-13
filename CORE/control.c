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

#ifndef _CONTROL_c_
    #define _CONTROL_c_

// Source files
#include "control/prerequisites.c"
#include "control/PID.cpp"
#include "control/safety.cpp"
#include "control/point.cpp"
#include "control/bezier.cpp"
#include "control/signal-condition.cpp"
#include "control/estimation.cpp"
#include "control/trajectory.cpp"
#include "control/controllers.cpp"

#endif // _CONTROL_c_