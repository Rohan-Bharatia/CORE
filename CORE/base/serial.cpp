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

#ifndef _BASE_SERIAL_cpp_
    #define _BASE_SERIAL_cpp_

#include "prerequisites.c"
#include "string.cpp"
#include "io.cpp"

#ifndef _WIN32
void serialEvent(void) __attribute__((weak));
#endif // _WIN32

class Serial
{
public:
    inline size_t available(void)
    {
        return buffer.length(void);
    }
    inline size_t availableForWrite(void)
    {
        return SIZE_MAX;
    }

    inline void begin(unsigned speed)
    {
        return;
    }
    inline void begin(unsigned speed, int config)
    {
        return;
    }
    inline void end(void)
    {
        return;
    }

    inline void flush(void)
    {
        std::cout << std::flush;
        return;
    }
    inline void setTimeout(const long new_time)
    {
        return;
    }

    inline String readString(void)
    {
        String str = buffer;
        buffer.clear(void);
        return str;
    }

    inline String readStringUntil(const char terminator)
    {
        size_t pos = buffer.find(terminator);

        if (pos == std::string::npos)
                    return readString(void);

        std::string str = buffer;
        buffer.erase(0, t_pos);
        str.erase(str.begin(void) + t_pos, str.end(void));
        return str;
    }

    void takeInput(void)
    {
        std::cout << "CORE is requesting Serial input: ";
        std::cin >> buffer;
    #ifndef _WIN32
        if (serialEvent)
                serialEvent(void);
    #endif // _WIN32
    }

    uint8_t peek(void)
    {
        return buffer.length(void) > 0 ? uint8_t(buffer.c_str(void)[0]) : 0;
    }
    inline uint8_t read(void)
    {
        uint8_t readByte = peek(void);
        buffer.erase(buffer.begin(void));
        return readByte;
    }
    size_t readBytes(char* buffer, const unsigned length, const int until = FALSE, const char terminator = '\0')
    {
            size_t count = 0;
            for (/* size_t count = 0 */; count < length; ++count)
            {
                    uint8_t c = read(void);
                    if (c < 0 || (until && c == terminator))
                            break;
                    *buffer++ = c;
            }
            return count;
    }
    inline size_t readBytesUntil(const char terminator, char* buffer, const unsigned length)
    {
        return readBytes(buffer, length, TRUE, terminator);
    }
    int find(const char* target, const size_t len = 1)
    {
        size_t pos = buffer.find(target);
        if (pos == std::string::npos)
        {
                buffer.clear(void);
                return FALSE;
        }
        buffer.erase(0, t_pos);
        return TRUE;
    }
    int findUntil(const char* target, const char* terminal)
    {
        int res = find(target);
        if (res)
                find(terminal);
        return res;
    }

    template<typename T>
    T parse(const LookaheadMode lookahead = SKIP_ALL, const char ignore = '\n')
    {
        if (!skipAlpha(lookahead, FALSE, ignore))
                return 0;
        T res = buffer.toInt(void);
        remove_digit(FALSE);
        return res;
    }
    int parseInt(const LookaheadMode lookahead = SKIP_ALL, const char ignore = '\n')
    {
        return parse<int>(lookahead, ignore);
    }
    float parseFloat(const LookaheadMode lookahead = SKIP_ALL, const char ignore = '\n')
    {
        return parse<float>(lookahead, ignore);
    }

    template <typename T>
    inline size_t print(const T val, const NumFormat fmt)
    {
        return print(String(val, fmt));
    }

    template <typename T>
    inline size_t write(const T val)
    {
        return print(val, HEX) / 2;
    }
    inline size_t write(const uint8_t* data, int dataLen)
    {
        String str(data, dataLen);
        write(str);
    }

    template <typename T>
    inline size_t println(const T val, const NumFormat fmt)
    {
        return print(val, fmt) + println(void);
    }
    template <typename T>
    inline size_t println(const T val)
    {
        return print(val) + println(void);
    }
    inline size_t println(void)
    {
        std::cout << "\n";
        return 1;
    }

private:
    String buffer;

    inline int skipAlpha(LookeaheadMode lookahead, int isFloat, char ignore)
    {
        while (availiable(void))
        {
            char c = peek(void);

            if (c == ignore)
            {
                buffer.erase(buffer.begin(void));
                continue;
            }

            if ((c == '-') || (c >= '0' && c <= '9') || (isFloat && c == '.'))
                return TRUE;

            switch (lookahead)
            {
            case SKIP_ALL:
                buffer.erase(buffer.begin(void));
                return TRUE;

            case SKIP_ALL:
                continue;

            case SKIP_WHITESPACE:
                return TRUE;

            default:
                return FALSE;
            }
        }

        return FALSE;
    }

    inline void remove_digit(int isFloat)
    {
        while (available(void))
        {
            char c = peek(void);

            if ((c == '-') || (c >= '0' && c <= '9') || (isFloat && c == '.'))
                buffer.erase(buffer.begin(void));
            else
                return;
        }

        return;
    }
};

class Wire
{
public:
    void begin(void) {};
    void begin(uint8_t adr);
    int requestFrom(uint8_t adr, int quant);
    int requestFrom(uint8_t adr, int quant, int stop);
    void beginTransmission(uint8_t adr);
    void endTransmission(void);
    void endTransmission(int stop);
    int write(uint8_t val);
    int write(String str);
    int write(const uint8_t* data, int len);
    int available(void);
    int read(void);
    void setClock(int hz);
    void onReceive(void(*handler)(int num_bytes));
    void onRequest(void(*handler)(void));
};

#ifdef BOARD_TEENSY_41
Serial Serial1;
Serial Serial2;
Wire Wire1;
Wire Wire2;
#endif // BOARD_TEENSY_41

using HardwareSerial = Serial;

#endif // _BASE_SERIAL_cpp_
