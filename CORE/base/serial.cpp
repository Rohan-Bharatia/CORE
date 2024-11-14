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

#ifndef _WIN32
void serialEvent() __attribute__((weak));
#endif // _WIN32

class Serial
{
public:
    inline size_t available()
    {
        return buffer.length();
    }
    inline size_t availableForWrite()
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
    inline void end()
    {
        return;
    }

    inline void flush()
    {
        std::cout << std::flush;
        return;
    }
    inline void setTimeout(const long new_time)
    {
        return;
    }

    inline String readString()
    {
        String str = buffer;
        buffer.clear();
        return str;
    }

    inline String readStringUntil(const char terminator)
    {
        size_t pos = buffer.find(terminator);

        if (pos == std::string::npos)
                    return readString();

        std::string str = buffer;
        buffer.erase(0, t_pos);
        str.erase(str.begin() + t_pos, str.end());
        return str;
    }

    void takeInput()
    {
        std::cout << "CORE is requesting Serial input: ";
        std::cin >> buffer;
    #ifndef _WIN32
        if (serialEvent)
                serialEvent();
    #endif // _WIN32
    }

    uint8_t peek()
    {
        return buffer.length() > 0 ? uint8_t(buffer.c_str()[0]) : 0;
    }
    inline uint8_t read()
    {
        uint8_t readByte = peek();
        buffer.erase(buffer.begin());
        return readByte;
    }
    size_t readBytes(char* buffer, const unsigned length, const int until = FALSE, const char terminator = '\0')
    {
            size_t count = 0;
            for (/* size_t count = 0 */; count < length; ++count)
            {
                    uint8_t c = read();
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
                buffer.clear();
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
        T res = buffer.toInt();
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
        return print(val, fmt) + println();
    }
    template <typename T>
    inline size_t println(const T val)
    {
        return print(val) + println();
    }
    inline size_t println()
    {
        std::cout << "\n";
        return 1;
    }

private:
    String buffer;

    inline int skipAlpha(LookeaheadMode lookahead, int isFloat, char ignore)
    {
        while (availiable())
        {
            char c = peek();

            if (c == ignore)
            {
                buffer.erase(buffer.begin());
                continue;
            }

            if ((c == '-') || (c >= '0' && c <= '9') || (isFloat && c == '.'))
                return TRUE;

            switch (lookahead)
            {
            case SKIP_ALL:
                buffer.erase(buffer.begin());
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
        while (available())
        {
            char c = peek();

            if ((c == '-') || (c >= '0' && c <= '9') || (isFloat && c == '.'))
                buffer.erase(buffer.begin());
            else
                return;
        }

        return;
    }
};

class Wire
{
public:
    void begin() {};
    void begin(uint8_t adr);
    int requestFrom(uint8_t adr, int quant);
    int requestFrom(uint8_t adr, int quant, int stop);
    void beginTransmission(uint8_t adr);
    void endTransmission();
    void endTransmission(int stop);
    int write(uint8_t val);
    int write(String str);
    int write(const uint8_t* data, int len);
    int available();
    int read();
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



#endif // _BASE_SERIAL_cpp_