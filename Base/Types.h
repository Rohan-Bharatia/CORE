#pragma region LICENSE

// MIT License
//
// Copyright (c) 2025 Rohan Bharatia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma endregion LICENSE

#pragma once

#ifndef _CORE_BASE_TYPES_H_
    #define _CORE_BASE_TYPES_H_

// Standard types
typedef unsigned int uint;
typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;
typedef long long int64;
typedef unsigned long long uint64;
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long long opsize;
typedef float float32;
typedef double float64;
typedef unsigned char bool;
typedef char* string;

// Default type macros
#define NULL    0
#define nullptr 0
#define true    1
#define false   0

// Integer constants
#define UINT_MIN   0
#define UINT_MAX   4294967295
#define INT8_MIN   -128
#define INT8_MAX   127
#define UINT8_MIN  0
#define UINT8_MAX  255
#define INT16_MIN  -32768
#define INT16_MAX  32767
#define UINT16_MIN 0
#define UINT16_MAX 65535
#define INT32_MIN  -2147483648
#define INT32_MAX  2147483647
#define UINT32_MIN 0
#define UINT32_MAX 4294967295
#define INT64_MIN  -9223372036854775808
#define INT64_MAX  9223372036854775807
#define UINT64_MIN 0
#define UINT64_MAX 18446744073709551615
#define BYTE_MIN   0
#define BYTE_MAX   255
#define WORD_MIN   0
#define WORD_MAX   65535
#define OPSIZE_MIN 0
#define OPSIZE_MAX 18446744073709551615

// ASCII character constants
#define ASCII_NULL 0x00
#define ASCII_0    0x30
#define ASCII_1    0x31
#define ASCII_2    0x32
#define ASCII_3    0x33
#define ASCII_4    0x34
#define ASCII_5    0x35
#define ASCII_6    0x36
#define ASCII_7    0x37
#define ASCII_8    0x38
#define ASCII_9    0x39
#define ASCII_A    0x41
#define ASCII_B    0x42
#define ASCII_C    0x43
#define ASCII_D    0x44
#define ASCII_E    0x45
#define ASCII_F    0x46
#define ASCII_G    0x47
#define ASCII_H    0x48
#define ASCII_I    0x49
#define ASCII_J    0x4A
#define ASCII_K    0x4B
#define ASCII_L    0x4C
#define ASCII_M    0x4D
#define ASCII_N    0x4E
#define ASCII_O    0x4F
#define ASCII_P    0x50
#define ASCII_Q    0x51
#define ASCII_R    0x52
#define ASCII_S    0x53
#define ASCII_T    0x54
#define ASCII_U    0x55
#define ASCII_V    0x56
#define ASCII_W    0x57
#define ASCII_X    0x58
#define ASCII_Y    0x59
#define ASCII_Z    0x5A

// Float constants
#define FLOAT32_MIN     1.401298464324817e-45
#define FLOAT32_MAX     3.4028234663852886e+38
#define FLOAT64_MIN     4.9406564584124654e-324
#define FLOAT64_MAX     1.7976931348623157e+308
#define FLOAT32_EPSILON 1.1920928955078125e-7
#define FLOAT64_EPSILON 2.2204460492503131e-16

#endif // _CORE_BASE_TYPES_H_
