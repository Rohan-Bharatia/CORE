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

#ifndef _CONTROL_POINT_cpp_
    #define _CONTROL_POINT_cpp_

template<typename T>
class Point
{
public:
    T x;
    T y;
    T z;

    Point(void) = default;
    Point(T x, T y, T z) : x(x), y(y), z(z)
    {
        return;
    }

    static const Point<T> ZERO((T)0.0, (T)0.0, (T)0.0);
    static const Point<T> ONE ((T)1.0, (T)1.0, (T)1.0);
};

// Setter operator
template <typename T> Point<T> = (Point<T> a, Point<T> b)
{
    return Point<T>(b.x, b.y, b.z);
}

// Relational operators
template<typename T> bool operator == (Point<T> a, Point<T> b)
{
    return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
}
template<typename T> bool operator != (Point<T> a, Point<T> b)
{
    return ((a.x != b.x) && (a.y != b.y) && (a.z != b.z));
}

template<typename T> bool operator < (Point<T> a, Point<T> b)
{
    return ((a.x < b.x) && (a.y < b.y) && (a.z < b.z));
}
template<typename T> bool operator > (Point<T> a, Point<T> b)
{
    return ((a.x > b.x) && (a.y > b.y) && (a.z > b.z));
}

template<typename T> bool operator <= (Point<T> a, Point<T> b)
{
    return ((a.x <= b.x) && (a.y <= b.y) && (a.z <= b.z));
}
template<typename T> bool operator >= (Point<T> a, Point<T> b)
{
    return ((a.x >= b.x) && (a.y >= b.y) && (a.z >= b.z));
}

// Arithmetic operators
template<typename T> Point<T> operator + (Point<T> a, Point<T> b)
{
    return Point<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}
template<typename T> Point<T> operator + (Point<T> a, T b)
{
    return Point<T>(a.x + b, a.y + b, a.z + b);
}

template<typename T> Point<T> operator - (Point<T> a, Point<T> b)
{
    return Point<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}
template<typename T> Point<T> operator - (Point<T> a, T b)
{
    return Point<T>(a.x - b, a.y - b, a.z - b);
}

template<typename T> Point<T> operator * (Point<T> a, Point<T> b)
{
    return Point<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}
template<typename T> Point<T> operator * (Point<T> a, T b)
{
    return Point<T>(a.x * b, a.y * b, a.z * b);
}

template<typename T> Point<T> operator / (Point<T> a, Point<T> b)
{
    return Point<T>(a.x / b.x, a.y / b.y, a.z / b.z);
}
template<typename T> Point<T> operator / (Point<T> a, T b)
{
    return Point<T>(a.x / b, a.y / b, a.z / b);
}

template<typename T> Point<T> operator % (Point<T> a, Point<T> b)
{
    return Point<T>(a.x % b.x, a.y % b.y, a.z % b.z);
}
template<typename T> Point<T> operator % (Point<T> a, T b)
{
    return Point<T>(a.x % b, a.y % b, a.z % b);
}

// Sign operators
template<typename T> Point<T> operator + (Point<T> a)
{
    return Point<T>(+a.x, +a.y, +a.z);
}
template<typename T> Point<T> operator - (Point<T> a)
{
    return Point<T>(-a.x, -a.y, -a.z);
}

// Unary operators
template<typename T> Point<T> operator ++ (Point<T> a)
{
    return a = a + (T)1.0;
}
template<typename T> Point<T> operator -- (Point<T> a)
{
    return a = a - (T)1.0;
}

// Assignment operators
template <typename T> Point<T> operator += (Point<T> a, Point<T> b)
{
    return a = a + b;
}
template <typename T> Point<T> operator += (Point<T> a, T b)
{
    return a = a + b;
}

template <typename T> Point<T> operator -= (Point<T> a, Point<T> b)
{
    return a = a - b;
}
template <typename T> Point<T> operator -= (Point<T> a, T b)
{
    return a = a - b;
}

template <typename T> Point<T> operator *= (Point<T> a, Point<T> b)
{
    return a = a * b;
}
template <typename T> Point<T> operator *= (Point<T> a, T b)
{
    return a = a * b;
}

template <typename T> Point<T> operator /= (Point<T> a, Point<T> b)
{
    return a = a / b;
}
template <typename T> Point<T> operator /= (Point<T> a, T b)
{
    return a = a / b;
}

template <typename T> Point<T> operator %= (Point<T> a, Point<T> b)
{
    return a = a % b;
}
template <typename T> Point<T> operator %= (Point<T> a, T b)
{
    return a = a % b;
}

// Logical operators
template<typename T> bool operator && (Point<T> a, Point<T> b)
{
    return ((a.x && b.x) && (a.y && b.y) && (a.z && b.z));
}
template<typename T> bool operator || (Point<T> a, Point<T> b)
{
    return ((a.x || b.x) && (a.y || b.y) && (a.z || b.z));
}
template<typename T> bool operator ! (Point<T> a)
{
    return ((!a.x) && (!a.y) && (!a.z));
}

// Bitwise operators
template<typename T> Point<T> operator & (Point<T> a, Point<T> b)
{
    return Point<T>(a.x & b.x, a.y & b.y, a.z & b.z);
}
template<typename T> Point<T> operator | (Point<T> a, Point<T> b)
{
    return Point<T>(a.x | b.x, a.y | b.y, a.z | b.z);
}
template<typename T> Point<T> operator ^ (Point<T> a, Point<T> b)
{
    return Point<T>(a.x ^ b.x, a.y ^ b.y, a.z ^ b.z);
}
template<typename T> Point<T> operator ~ (Point<T> a)
{
    return Point<T>(~a.x, ~a.y, ~a.z);
}

template<typename T> void operator << (Point<T> a, uint16_t shift)
{
    Point<T>(a.x << shift, a.y << shift, a.z << shift);
    return;
}
template<typename T> void operator >> (Point<T> a, uint16_t shift)
{
    Point<T>(a.x >> shift, a.y >> shift, a.z >> shift);
    return;
}

typename Point<int>    PointI;
typename Point<float>  PointF;
typename Point<double> PointD;

#endif // _CONTROL_POINT_cpp_