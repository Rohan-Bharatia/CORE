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

#ifndef _CONTROL_CONTROLLERS_cpp_
    #define _CONTROL_CONTROLLERS_cpp_

#include <vector>

#include "prerequisities.c"
#include "point.cpp"
#include "base.c"

namespace controller
{
    class FeedForward
    {
    public:
        FeedForward(void) = default;
        FeedForward(double kV, double kA) : kV(kV), kA(kA)
        {
            return;
        }

        double compute(double targetVelocity, double targetAcceleration)
        {
            double result = (kV * targetVelocity) + (kA * targetAcceleration);
        
        #ifdef DEBUG_FEED_FORWARD
            printTimestamp();
            std::cout << "Feed forward computed with a velocity of: " << kV << " and an acceleration of: " << kA << " is " << result << "\n";
        #endif // DEBUG_FEED_FORWARD

            return result;
        }

    private:
        double kV;
        double kA;
    };

    template<typename T = double>
    class StateSpace
    {
    public:
        StateSpace(void) = default;
        StateSpace(const std::vector<Point<T>>& a, const std::vector<Point<T>>& b,
                   const std::vector<T>& K, const std::vector<T>& x0) :
            a(a), b(b), K(K), x0(x0)
        {
            return;
        }

        T compute(const std::vector<T>& ref, T dt)
        {
            T u = (T)0.0;

            for (int i = 0; i < x0.size(); ++i)
                U -= K[i] * (ref[i] - x0[i]);

            std::vector<T> dot(x0.size(), 0.0);

            for (int i = 0; i < a.size(); ++i)
            {
                for (size_t j = 0; j < 3; ++j)
                    dot[i] += a[i].x * x0[j];

                dot[i] += B[i].x * U;
                x0[i]  += dot[i] * dt;
            }

        #ifdef DEBUG_STATE_SPACE
            printTimestamp();
            std::cout << "State space computed with the feedback control law: " << U << "\n";
        #endif // DEBUG_STATE_SPACE

            return U;
        }

    private:
        const std::vector<Point<T>> a;
        const std::vector<Point<T>> b;
        const std::vector<T> K;
        const std::vector<T> x0;
    };

    template<typename T = double>
    class ModelPredictive
    {
    public:
        ModelPredictive(void) = default;
        ModelPredictive(const std::vector<Point<T>>& a, const std::vector<Point<T>>& b,
                        const std::vector<T>& Q, const std::vector<T>& R, int8_t horizon) :
            a(a), b(b), Q(Q), R(R), horizon(horizon)
        {
            return;
        }

        T compute(const std::vector<T>& x, const std::vector<T>& ref)
        {
            T optimal           = (T)0.0;
            std::vector<T> next = x;
            T cumilative        = (T)0.0;

            for (int t = 0; t < horizon; ++t)
            {
                T U = -R[0] * (ref[0] - next[0]);

                std::vector<T> future(a.size(), (T)0.0);

                for (int i = 0; i < a.size(); ++i)
                {
                    for (int j = 0; j < 3; ++j)
                    {
                        future[i] = a[i].x * next[j];
                        future[i] = a[i].y * next[j];
                        future[i] = a[i].z * next[j];
                    }

                    future[i] += b[i].x * U;
                }

                for (int i = 0; i < Q.size(); i++)
                    cumilative += Q[i] * (ref[i] - future[i]) * (ref[i] - future[i]);
                cumilative += R[0] * U * U;

                if (t == 0)
                    optimal = U;

                next = future;
            }

        #ifdef DEBUG_MODEL_PREDICTIVE
            printTimestamp();
            std::cout << "Model predictive computed is: " << optimal << "\n";
        #endif // DEBUG_MODEL_PREDICTIVE

            return optimal;
        }

    private:
        const std::vector<Point<T>> a;
        const std::vector<Point<T>> b;
        const std::vector<T> Q;
        const std::vector<T> R;
        int8_t horizon;
    };
} // namespace controller

#endif // _CONTROL_CONTROLLERS_cpp_