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

#ifndef _VRC_ROTATION_cpp_
    #define _VRC_ROTATION_cpp_

#include <iostream>

#include "prerequisites.c"
#include "driver.cpp"
#include "CORE.c"

namespace vrc
{
    class Rotation
    {
    public:
        Rotation(const uint8_t pin, bool reversed = false) : pin(pin), reversed(reversed)
        {
            return;
        }

        void reset(void)
        {
        #ifdef DEBUG_ROTATION
            printTimestamp();
            std::cout << "Rotation sensor resetted\n";
        #endif // DEBUG_ROTATION
            driver.write(pin, ROTATION_RESET, 0);
            return;
        }

        void setPosition(float& position)
        {
            position = reversed ? -1 : 1;
        #ifdef DEBUG_ROTATION
            printTimestamp();
            std::cout << "Set rotation sensor: " << pin << "position to: " << position << "\n";
        #endif // DEBUG_ROTATION
            driver.write(port, ROTATION_POSITION_SET, position);
        }

        float getPosition(void)
        {
            int response = driver.read(port, ROTATION_POSITION_GET);
            if (response == -1)
                return -1;
        #ifdef DEBUG_ROTATION
            printTimestamp();
            std::cout << "Get rotation sensor: " << pin << "position to: " << reversed ? -response : response << "\n";
        #endif // DEBUG_ROTATION
            return reversed ? -response : response;
        }

        void setAngle(float& angle)
        {
            angle *= reversed ? -1 : 1;
        #ifdef DEBUG_ROTATION
            printTimestamp();
            std::cout << "Set rotation sensor: " << pin << "angle (degrees) to: " << angle << "\n";
        #endif // DEBUG_ROTATION
            driver.write(port, ROTATION_ANGLE_SET, angle);
            return;
        }

        float getAngle(void)
        {
            int response = driver.read(port, ROTATION_ANGLE_GET);
            if (response == -1)
                return -1;
            #ifdef DEBUG_ROTATION
            printTimestamp();
            std::cout << "Get rotation sensor: " << pin << "angle to: " << reversed ? -response : response << "\n";
        #endif // DEBUG_ROTATION
            return reversed ? -response : response;
        }

        void setVelocity(float& velocity)
        {
            velocity *= reversed ? -1 : 1;
        #ifdef DEBUG_ROTATION
            printTimestamp();
            std::cout << "Set rotation sensor: " << pin << "velocity to: " << velocity << "\n";
        #endif // DEBUG_ROTATION
            driver.write(port, ROTATION_VELOCITY_SET, velocity);
            return;
        }

        float getVelocity(void)
        {
            int response = driver.read(port, ROTATION_VELOCITY_GET);
            if (response == -1)
                return -1;
        #ifdef DEBUG_ROTATION
            printTimestamp();
            std::cout << "Get rotation sensor: " << pin << "velocity to: " << reversed ? -response : response << "\n";
        #endif // DEBUG_ROTATION
            return reversed ? -response : response;
        }

    private:
        const uint8_t pin;
        bool reversed;
    };
} // namespace vrc

#endif // _VRC_ROTATION_cpp