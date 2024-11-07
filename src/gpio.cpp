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

#ifndef _CORE_GPIO_c_
    #define _CORE_GPIO_c_

#include "int.c"

#define GPIO_BASE      0x50000000 // Base address for GPIO
#define GPIO_INPUT     (volatile uint32*)(GPIO_BASE + 0x08) // Input register (read)
#define GPIO_OUTPUT    (volatile uint32*)(GPIO_BASE + 0x04) // Output register (write)
#define GPIO_DIRECTION (volatile uint32*)(GPIO_BASE + 0x00) // Direction register

#define INPUT  0 // Input code
#define OUTPUT 1 // Output code

#define HIGH 1 // High value
#define LOW  0 // Low value

// General purpose Input Output code
class GPIO
{
public:
    static void setup(uint32 base)
    {
        GPIO_BASE &= 0x00000000;
        GPIO_BASE |= base;
        return;
    }
    // Sets the direction of a GPIO pin
    static void setPin(uint32 pin, uint8 direction)
    {
        switch(direction)
        {
            case INPUT:  *GPIO_DIRECTION |= ~(1 << pin); return;
            case OUTPUT: *GPIO_DIRECTION |=  (1 << pin); return;
            default:     *GPIO_DIRECTION &=  0x00000000; return;
        }
    }

    // Reads data from a GPIO pin
    static uint8 read(uint32 pin)
    {
        return ((*GPIO_INPUT >> pin) & 1);
    }

    // Writes data to a GPIO pin
    static void write(uint32 pin, uint8 value)
    {
        switch(value)
        {
            case LOW:  *GPIO_OUTPUT |= ~(1 << pin); return;
            case HIGH: *GPIO_OUTPUT |=  (1 << pin); return;
            default:   *GPIO_OUTPUT &=  0x00000000; return;
        }
    }
};

// Waits for a specified time (in milliseconds)
static void delay(uint32 millis)
{
    for (volatile uint32 i = 0; i < millis; i++);
    return;
}

#endif // _CORE_GPIO_c_