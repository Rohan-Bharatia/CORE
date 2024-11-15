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

#ifndef _ALGORITHM_DRIVETRAIN_cpp_
    #define _ALGORITHM_DRIVETRAIN_cpp_

#include <vector>
#include <iostream>
#include <pair>
#include <cmath>

#include "prerequisites.c"
#include "control.c"
#include "subsystem.c"
#include "base.c"

class Drivetrain
{
public:
    Drivetrain(void) = default;
    Drivetrain(std::vector<motor::Stepper> left, std::vector<motor::Stepper> right, double radius, double basewidth) : 
        left(left), right(right), radius(radius), basewidth(basewidth)
    {
        return;
    }

    void setPose(Pose pose) : pose(pose)
    {
    #ifdef DEBUG_DRIVETRAIN
        printTimestamp();
        std::cout << "Write pose: " << pose << "\n";
    #endif // DEBUG_DRIVETRAIN
        return;
    }

    void drive(double distance)
    {
        auto steps = calculateSteps(distance);
        setMotorsDirection({ direction >= 0 ? RIGHT : LEFT, direction >= 0 ? RIGHT : LEFT });
        stepMotors(steps);
    #ifdef DEBUG_DRIVETRAIN
        printTimestamp();
        std::cout << "Drive for: " << std::abs(distance) << " meters " << (direction >= ? "forward\n" : "backwards\n");
    #endif // DEBUG_DRIVETRAIN
        return;
    }

    void turn(double degrees) // -180 <-> 180
    {
        auto steps = calculateStepsForTurn(degrees);
        setMotorsDirection({ degrees >= 0 ? RIGHT : LEFT, degrees >= 0 ? LEFT : RIGHT });
        stepMotors(steps);
    #ifdef DEBUG_DRIVETRAIN
        printTimestamp();
        std::cout << "Turn for: " degrees << " degrees\n";
    #endif // DEBUG_DRIVETRAIN
        return;
    }

    void turnTo(PointD point)
    {
        double m1    = std::tan(std::atan((pose.position.y / pose.position.x) - pose.position.theta));
        double m2    = (point.y - pose.position.y) / (point.x - pose.position.x);
        double theta = std::atan(std::abs((m2 - m1) / ((m2 * m1) + 1)));
    #ifdef DEBUG_DRIVETRAIN
        printTimestamp();
        std::cout << "Turn to: " point << "\n";
    #endif // DEBUG_DRIVETRAIN
        turn(theta);
    }

    void driveTo(Pose goal, const std::vector<std::vector<PointD>> map)
    {
        AStar as(map);
        Node* a = { pose.position, INT_MAX, 0, nullptr };
        Node* b = { goal.position, INT_MAX, 0, nullptr };
        Bezier curve(as.findPath(a, b));
        for (auto& point : curve.generate(200))
        {
            turnTo(point);
            drive(goal.position - pose.position);
        }
    #ifdef DEBUG_DRIVETRAIN
        printTimestamp();
        std::cout << "Drive to: " goal << " on curve: " << curve << "\n";
    #endif // DEBUG_DRIVETRAIN
        return;
    }

    void stop(void)
    {
    #ifdef DEBUG_DRIVETRAIN
        printTimestamp();
        std::cout << "Stop drivetrain\n";
    #endif // DEBUG_DRIVETRAIN
        for (auto& motor : left)
            motor.stop();
        for (auto& motor : right)
            motor.stop();
        return;
    }

    void setSpeed(double speed)
    {
        for (auto& motor : left)
            motor.setSpeed(speed);
        for (auto& motor : right)
            motor.setSpeed(speed);
    #ifdef DEBUG_DRIVETRAIN
        printTimestamp();
        std::cout << "Write speed: " << speed << "\n";
    #endif // DEBUG_DRIVETRAIN
        return;
    }

private:
    std::vector<motor::Stepper> left;
    std::vector<motor::Stepper> right;
    double radius;
    double basewidth;
    Pose pose;

    std::pair<int, int> calculateSteps(double distance) const
    {
        return { ((distance / (TAU * radius)) * left.front().getMax()), ((distance / (TAU * radius)) * right.front().getMax()) };
    }
    std::pair<int, int> calculateStepsForTurn(double degrees) const
    {
        return { calculateSteps(PI * basewidth * (degrees / 360)).first, -calculateSteps(PI * basewidth * (degrees / 360)).second };
    }

    void setMotorsDirection(std::pair<int, int> dir)
    {
        for(auto& motor : left)
            motor.setDirection(dir.first);
        for(auto& motor : right)
            motor.setDirection(dir.second);
        return;
    }

    void stepMotors(std::pair<int, int> steps)
    {
        for (auto& motor : left)
            motor.stepFor(steps.first);
        for (auto& motor : right)
            motor.stepFor(steps.second);
        return;
    }
};

#endif // _ALGORITHM_DRIVETRAIN_cpp_