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

#ifndef _BASE_STRING_cpp_
    #define _BASE_STRING_cpp_

#include <cstring>
#include <sstream>
#include <string>
#include <bitset>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cstdlib>

#include "prerequisites.c"

class String : public std::string
{
    String()
    {
        return;
    }

    template<typename T>
    String(const T val)
    {
        std::stringstream s;
        s << val;
        append(s.str());
        return;
    }

    template <typename T>
    String(const T val, const NumFormat fmt)
    {
        std::stringstream s = {};
        switch (fmt)
        {
        case BIN:
        {
            std::bitset<sizeof(val) * 8> bits(val);
            s << bits;
            append(s.str());
            return;
        }
        case DEC:
        {
            break;
        }
        case HEX:
        {
            s << std::hex;
            break;
        }
        case OCT:
        {
            s << std::oct;
            break;
        }
        }
        s << (long)val;
        append(s.str());
        return;
    }

    String(const char* buff, const NumFormat fmt)
    {
        for (unsigned int i = 0; i < strlen(buff); ++i)
            append(String((uint8_t)buff[i], fmt));
        return;
    }

    String(const double val, const uint8_t decimals)
    {
        std::stringstream s;
        s << std::fixed << std::setprecision(decimals) << val;
        append(s.str());
        return;
    }

    inline float toFloat()
    {
        return std::stof(c_str());
    }
    inline int toInt()
    {
        return std::stoi(c_str());
    }
    inline double toDouble()
    {
        return std::atof(c_str());
    }
    inline void getBytes(byte* buf, unsigned len)
    {
        strncpy((char*)buf, substr(0, len).c_str(), len);
        return;
    }
    inline void toCharArray(unsigned char* buf, const unsigned len)
    {
        getBytes((byte*)buf, len); buf[len] = '\0';
        return;
    }

    inline String substring(size_t pos = 0, size_t len = npos)
    {
        return substr(pos, len);
    }

    inline void toLowerCase()
    {
        std::transform(begin(), end(), begin(), [](char c) { return std::tolower(c); });
        return;
    }
    inline void toUpperCase()
    {
        std::transform(begin(), end(), begin(), [](char c) { return std::toupper(c); });
        return;
    }

    inline char charAt(const unsigned int n)
    {
        return at(n);
    }
    inline int compareTo(const String str2)
    {
        return compare(str2);
    }

    template <typename T>
    inline int concat(const T val)
    {
        append(String(val));
        return TRUE;
    }

    inline int startsWith(const String substr)
    {
        return rfind(substr, 0) == 0;
    }
    inline int endsWith(const String str) 
    {
        return compare(length() - str.length(), str.length(), str) == 0;
    }
    inline int equals(const String str2)
    {
        return compare(str2) == 0;
    }

    int equalsIgnoreCase(const String str2)
    {
            String strlwr  = String(c_str()).toLowerCase();
            String str2lwr = String(str2.c_str()).toLowerCase();
            return strlwr.compare(str2lwr) == 0;
    }

    inline size_t indexOf(const char* val, const size_t from = 0)
    {
        return find(val, from);
    }
    inline size_t lastIndexOf(const char* val, const size_t from = 0)
    {
        return rfind(val, from);
    }

    inline void remove(const size_t index, const size_t count = 1)
    {
        erase(index, count);
        return;
    }

    void replace(const String from, const String to)
    {
        size_t start_pos = 0;
        while ((start_pos = find(from, start_pos)) != npos)
        {
                std::string::replace(start_pos, from.length(), to);
                start_pos += to.length();
        }
        return;
    }
    inline void setCharAt(const size_t index, const char c)
    {
        at(index) = c;
        return;
    }

    void trim()
    {
        erase(begin(), std::find_if(begin(), end(), [](char ch) { return !std::isspace(ch); }));
        erase(std::find_if(rbegin(), rend(), [](char ch) { return !std::isspace(ch); }).base(), end());
        return;
    }
};

#endif // _BASE_STRING_cpp_