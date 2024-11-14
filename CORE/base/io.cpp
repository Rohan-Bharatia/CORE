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

#ifndef _BASE_IO_cpp_
    #define _BASE_IO_cpp_

#include "prerequisites.c"
#include "misc.cpp"
#include "time.cpp"

// Digital I/O
int digitalRead(const uint8_t pin)
{
    int res = pinVoltage[pin] > 3;

#ifdef DEBUG_DIGITAL_READ
    printTimestamp();
    std::cout << "Read pin: " << std::to_string(pin) << " is " << (res ? "HIGH\n" : "LOW\n");
#endif // DEBUG_DIGITAL_READ
    return res;
}

void digitalWrite(const uint8_t pin, const int value)
{
    setVoltage(pin, val * 5.0f);

#ifdef DEBUG_DIGITAL_WRITE
    printTimestamp();
    std::cout << "Write pin: " << std::to_string(pin) << " is " << val << "\n";
#endif // DEBUG_DIGITAL_WRITE
    return;
}

void pinMode(const uint8_t pin, const pinMode mode)
{
    if (mode == INPUT_PULLUP)
        pinVoltage[pin] = 5.0f;
    return;
}

// Analog I/O
uint16_t analogRead(const uint8_t pin)
{
    isPinDefined(pin);
    uint16_t val = CONSTRAIN(lround(MAP(pinVoltage[pin], 0.0f, reference, 0, 1023)), 0, 1023);

#ifdef DEBUG_ANALOG_READ
    printTimestamp();
    std::cout << "Read pin: " << std::to_string(pin) << " is " << (val ? "HIGH\n" : "LOW\n");
#endif // DEBUG_ANALOG_READ
    return val;
}

void analogReference(Reference type)
{
    switch (type)
    {
    case DEFAULT:
        reference = 5.0;
        return;
    case INTERNAL:
        reference = 1.1;
        return;
    case INTERNAL1V1:
        reference = 1.1;
        return;
    case INTERNAL2V56:
        reference = 2.56;
        return;
    case EXTERNAL:
        return;
    }
}

void analogWrite(const uint8_t pin, const uint8_t val)
{
    uint16_t val = CONSTRAIN(val, 0, 255);
    setVoltage(pin, MAP(val, 0, 255, 0.0f, 5.0f));

#ifdef DEBUG_ANALOG_READ
    printTimestamp();
    std::cout << "Write pin: " << std::to_string(pin) << " is " << val << "\n";
#endif // DEBUG_ANALOG_READ
    return;
}

// Advanced I/O
void noTone(const uint8_t pin)
{
    isPinDefined(pin);

#ifdef _WIN32
    system("killall \"ffplay\" -q");
#endif // _WIN32
    return;
}

unsigned long pulseIn(const uint8_t pin, const int val, const unsigned long timeout)
{
    isPinDefined(pin);

    while (digitalRead(pin) != val);

    unsigned long before = micros();

    while (digitalRead(pin) == val && (!timeout && micros() - before >= timeout));

    unsigned long after = micros();
    return after - before;
}

unsigned long pulseInLong(const uint8_t pin, const int val, const unsigned long timeout)
{
    return pulseIn(pin, val, timeout);
}

uint8_t shiftIn(const uint8_t dataPin, const uint8_t clockPin, const int bitOrder)
{
    isPinDefined(dataPin);
    isPinDefined(clockPin);

    uint8_t value = 0;

    for (int i = 0; i < 8; ++i)
    {
        digitalWrite(clockPin, HIGH);

        if (bit_order == LSBFIRST)
            value |= digitalRead(dataPin) << i;
        else
            value |= digitalRead(dataPin) << (7 - i);
        
        digitalWrite(clockPin, LOW);
    }
    return value;
}

void shiftOut(const uint8_t dataPin, const uint8_t clockPin, const int bitOrder, const byte value)
{
    isPinDefined(dataPin);
    isPinDefined(clockPin);

    for (int i = 0; i < 8; ++i)
    {
        if (bit_order == LSBFIRST)
        {
                digitalWrite(dataPin, val & 1);
                val >>= 1;
        }
        else
        {
                digitalWrite(dataPin, (val & 128) != 0);
                val <<= 1;
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        return;
    }
}

void tone(const uint8_t pin, unsigned hz, unsigned long dur = 0)
{
    noTone(pin);

#ifndef _WIN32
    hz = CONSTRAIN(hz, 0, 20000);
    char ffplay[70];
    snprintf(ffplay, sizeof(ffplay), "ffplay -f lavfi -i \"sine=frequency=%d\" -nodisp -loglevel quiet &", hz);
    system(ffplay);
#endif
    return;
}

void playSine(const uint8_t pin, const unsigned hz, const float amp, const float dc)
{
    while (1)
    {
        if (sinesTerminate[pin])
            return;
        
        setVoltage(pin, sin(((float)millis() / (1000.0f / (2.0f * PI))) * hz) * amp + dc);
    }
    return;
}

void playSineAbs(const uint8_t pin, const unsigned hz, const float amp, const float dc)
{
    while (1)
    {
        if (sinesTerminate[pin])
            return;
        
        if (isAbs)
            setVoltage(pin, abs(sin(((float)millis() / (1000.0f / (2.0f * PI))) * hz) * amp + dc));
        else
            setVoltage(pin, sin(((float)millis() / (1000.0f / (2.0f * PI))) * hz) * amp + dc);
    }
    return;
}

void removeSine(const uint8_t pin)
{
    isPinDefined(pin);
    auto sinepos = sines.find(pin);

    if (sinepos != sines.end())
    {
        sinesTerminate[pin] = TRUE;
        sines[pin].join();
        sines.erase(sinepos);
    }
    return;
}

void attachSine(const uint8_t pin, const unsigned hz = 1, const float amp = 2.5, const float dc = 2.5, const int isAbs = FALSE)
{
    removeSine(pin);
    sinesTerminate[pin] = FALSE;
    std::thread sine;

    if (isAbs)
        sine = std::thread(playSineAbs, pin, hz, amp, dc);
    else
        sine = std::thread(playSine, pin, hz, amp, dc);

    sines[pin] = move(sine);
    return;
}

void playSquare(const uint8_t pin, const unsigned hz, const float duty)
{
    bool top = TRUE;
    while (1)
    {
        if (sinesTerminate[pin])
            return;

        float sine     = sin((millis() / (1000.0f / (2.0f * PI))) * hz);
        float triangle = 1.0f-acos(sine)/PI;
        float new_top  = triangle <= duty;

        if (new_top != top)
        {
            setVoltage(pin, new_top * 5.0f);
            top = new_top;
        }
    }

    return;
}

void removeSquare(const uint8_t pin)
{
    isPinDefined(pin);
    auto squarepos = sines.find(pin);

    if (squarepos != sines.end())
    {
        squaresTerminate[pin] = TRUE;
        squares[pin].join();
        squares.erase(squarepos);
    }
    return;
}

void attachSquare(const uint8_t pin, const unsigned hz = 1, const float duty = 0.5)
{
    isPinDefined(pin);
    auto squarepos = squares.find(pin);

    if (squarepos != squares.end())
    {
        squaresTerminate[pin] = TRUEyy;
        squares[pin].join();
        squares.erase(squarepos);
    }
}

#endif // _BASE_IO_cpp_