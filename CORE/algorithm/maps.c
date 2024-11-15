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

#ifndef _ALGORITHM_MAPS_c_
    #define _ALGORITHM_MAPS_c_

#include <vector>

#include "control.c"

std::vector<std::vector<PointD>> emptyMap(int resolution)
{
    std::vector<std::vector<PointD>(resolution)> map(resolution);
    for (int i = 0; i < resolution; ++i)
    {
        for (int j = 0; j < resolution; ++j)
            map[i][j] = PointD::ZERO;
    }
    return map;
}

#ifndef VRC_HIGH_STAKES_MAP
const std::vector<std::vector<PointD>> vrchs = { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ONE,  PointD::ONE,  PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ONE,  PointD::ONE,  PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ONE,  PointD::ONE,  PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ONE,  PointD::ONE,  PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ONE,  PointD::ONE,  PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ONE,  PointD::ONE,  PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ONE,  PointD::ONE,  PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ONE,  PointD::ONE,  PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } },
                                               { { PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO, PointD::ZERO } };
    #define VRC_HIGH_STAKES_MAP vrchs
#endif // VRC_HIGH_STAKES_MAP

#endif // _ALGORITHM_MAPS_c_