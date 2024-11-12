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

#ifndef _CORE_INTERRUPT_cpp_
    #define _CORE_INTERRUPT_cpp_

#include "prerequisites.c"

// Pin interrupt
#define DIGITAL_PIN_TO_INTERRUPT(pin) (pin)

void detachInterrupt(const uint8_t pin)
{
    isPinDefined(pin);
    auto intpos = ints.find(pin);

    if(intpos != ints.end())
        ints.erase(intpos);
    return;
}

void attachInterrupt(const uint8_t pin, void(*intpointer)(void), const IntMode mode)
{
    detachInterrupt(pin);
    ints[pin] = { intpointer, mode };
    return;
}
inline void interrupts(void)
{
    interruptsEnabled = TRUE;
    return;
}
inline void noInterrupts(void)
{
    interruptsEnabled = FALSE;
    return;
}

#endif // _CORE_INTERRUPT_cpp_