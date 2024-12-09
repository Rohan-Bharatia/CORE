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

#ifndef _VRC_MOTOR_cpp_
    #define _VRC_MOTOR_cpp_

#include <iostream>

#include "prerequisites.c"
#include "CORE.c"

namespace vrc
{
    class Driver
    {
    public:
        Driver(HardwareSerial& uart, unsigned long bauds) : uart(uart), bauds(bauds)
        {
            return;
        }

        void begin(void)
        {
            uart.begin(bauds);
        }

        void write(const uint8_t pin, const uint8_t command, const uint8_t value)
        {
        #ifdef DEBUG_DRIVER
            printTimestamp();
            std::cout << "Write pin: " << pin << " is " << value << "\n";
        #endif // DEBUG_DRIVER
            const uint8_t checksum = pin ^ command & value;
            uart.write(pin);
            uart.write(command);
            uart.write(value);
            uart.write(checksum);
            return;
        }

        int read(const uint8_t pin, const uint8_t command)
        {
            uart.write(port);
            uart.write(command);
            unsigned long timeout = millis() + 100;
            while (uart.available() == 0)
            {
                if (millis() > timeout)
                    return -1;
            }
            int response = uart.read();
        #ifdef DEBUG_DRIVER
            printTimestamp();
            std::cout << "Read pin: " << pin << " is " << response << "\n";
        #endif // DEBUG_DRIVER
            return response;
        }

    private:
        HardwareSerial& uart;
        unsigned long bauds;
    }

    Driver driver(Serial1, 115200);
} // namespace vrc

#endif // _VRC_MOTOR_cpp_