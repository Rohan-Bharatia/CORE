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

#ifndef _CORE_PREREQUISITES_c_
    #define _CORE_PREREQUISITES_c_

#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <unordered_map>
#include <iostream>

// Defines
#define LOW      0
#define HIGH     1
#define MBSFIRST 0
#define LBSFIRST 1
#define TRUE     1
#define FALSE    0

// enumerators
typedef enum PinMode
{
    INPUT,
    OUTPUT,
    INPUT_PULLUP
} PinMode;

typedef enum NumFormat
{
    BIN,
    OCT,
    DEC,
    HEX
} NumFormat;

typedef enum IntMode : uint64_t
{
    CHANGE,
    FALLING,
    RISING
} IntMode;

typedef enum LookeaheadMode
{
    SKIP_NONE,
    SKIP_WHITESPACE,
    SKIP_ALL
} LookeaheadMode;

typedef enum Reference
{
    DEFAULT,
    INTERNAL,
    INTERNAL1V1,
    INTERNAL2V56,
    EXTERNAL
} Reference;

typedef enum PinType
{
    ANALOG,
    DIGITAL,
    PWM,
    INT
} PinType;

typedef struct Int
{
    void (*intpointer)(void);
    IntMode mode;
} Int;

// Unordered maps
std::unordered_map<uint8_t, Int> ints;
std::unordered_map<uint8_t, std::thread> sines;
std::unordered_map<uint8_t, int> sinesTerminate;
std::unordered_map<uint8_t, std::thread> squares;
std::unordered_map<uint8_t, int> squaresTerminate;
int interruptsEnabled = TRUE;
float reference       = 5.0f;

// Types
#define byte uint8_t
#define word uint16_t

#ifdef DEBUG_ALL
    #define DEBUG_DIGITAL_READ
    #define DEBUG_DIGITAL_WRITE
    #define DEBUG_ANALOG_READ
    #define DEBUG_ANALOG_WRITE
#endif // DEBUG_ALL

#ifdef BOARD_PRO_MINI
    #define BOARD_PRO
#endif // BOARD_PRO_MINI

// Arduino Teensy
#if defined(TEENSY_41)
    #define MAX_PINS 42

enum AnalogPin
{
    LED_BUILTIN = 13,
    A0          = 14,
    A1          = 15,
    A2          = 16,
    A3          = 17,
    A4          = 18,
    A5          = 19,
    A6          = 20,
    A7          = 21,
    A8          = 22,
    A9          = 23,
    A10         = 24,
    A11         = 25,
    A12         = 26,
    A13         = 27,
    A14         = 38,
    A15         = 39,
    A16         = 40,
    A17         = 41
};

// Arduino Nano or Ardiuno Pro
#elif defined(BOARD_NANO) || defined(BOARD_PRO)
    #define MAX_PINS 21

enum AnalogPin
{
    LED_BUILTIN = 13,
    A0          = 14,
    A1          = 15,
    A2          = 16,
    A3          = 17,
    A4          = 18,
    A5          = 19,
    A6          = 20,
    A7          = 21
};

// Arduino Uno
#elif defined(BOARD_UNO)
    #define MAX_PINS 19

enum AnalogPin
{
    LED_BUILTIN = 13,
    A0          = 14,
    A1          = 15,
    A2          = 16,
    A3          = 17,
    A4          = 18,
    A5          = 19,
};
#else // (NOT) defined(TEENSY_41) - defined(BOARD_NANO) || defined(BOARD_PRO) - defined(BOARD_UNO)
    #define CREATE_NEW_BOARD_ANALOG(...) enum AnalogPin { __VA_ARGS__ }
#endif // defined(TEENSY_41) - defined(BOARD_NANO) || defined(BOARD_PRO) - defined(BOARD_UNO)

// Entry points
void setup(void);
void loop(void);
void isPinDefined(const uint8_t pin, const PinType = DIGITAL);

unsigned long startTimeMillis;
unsigned long startTimeMicros;

#define AREF 255
float pinVoltage[MAX_PINS] = { 0 };

// Math functions/constants
#define CLAMP(x, a, b)         ({x = x < a ? a : x; x = x > b ? b : x;})
#define MAP(x, fL, fH, tL, tH) ((x - fL) * (tH - tL) / (fH - fL) + tL)
#define MIN(a,b)               ((a)<(b)?(a):(b))
#define MAX(a,b)               ((a)>(b)?(a):(b))
#define SQR(x)                 ((x)*(x))
#define PI                     atan(1) * 4
#define TAU                    atan(1) * 8

// Characthers
#define isAlpha(thisChar)            (isalpha(thisChar))
#define isAlphaNumeric(thisChar)     (isalnum(thisChar))
#define isAscii(thisChar)            (TRUE)
#define isControl(thisChar)          (iscntrl(thisChar))
#define isDigit(thisChar)            (isdigit(thisChar))
#define isGraph(thisChar)            (isgraph(thisChar))
#define isHexadecimalDigit(thisChar) (isxdigit(thisChar))
#define isLowerCase(thisChar)        (islower(thisChar))
#define isPrintable(thisChar)        (isprint(thisChar))
#define isPunct(thisChar)            (ispunct(thisChar))
#define isSpace(thisChar)            (isspace(thisChar))
#define isUpperCase(thisChar)        (isupper(thisChar))
#define isWhitespace(thisChar)       (isspace(thisChar))

// Bits and Bytes
#define bit(b)                         (1UL << (b))
#define bitRead(value, bit)            (((value) >> (bit)) & 0x01)
#define bitSet(value, bit)             ((value) |= (1UL << (bit)))
#define bitClear(value, bit)           ((value) &= ~(1UL << (bit)))
#define bitToggle(value, bit)          ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))
#define highByte(w)                    ((uint8_t) ((w) >> 8))
#define lowByte(w)                     ((uint8_t) ((w) & 0xff))

void isPinDefined(const uint8_t pin, const PinType = DIGITAL)
{
    if (pin > AN_MAX_PINS && pin != AREF)
    {
        std::cout << "ERROR: PIN " << std::to_string(pin) << " IS NOT DEFINED\n";
        exit(1);
    }

    exit(0);
}

#endif // _CORE_PREREQUISITES_c_