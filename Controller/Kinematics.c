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

#ifndef _CORE_CONTROLLER_KINEMATICS_C_
    #define _CORE_CONTROLLER_KINEMATICS_C_

#include "Kinematics.h"

#include <math.h>

float32 distance(Vector3D* a, Vector3D* b)
{
    return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y) + (a->z - b->z) * (a->z - b->z));
}

Vector3D* forwardKinematics(Vector3D* joints)
{
    Vector3D* endEffector;

    // Simple 3-DOF robot arm kinematics
    float32 l1 = 1.0f;
    float32 l2 = 1.0f;
    float32 l3 = 1.0f;

    float32 cx = cosf(joints->x);
    float32 sx = sinf(joints->x);
    float32 cy = cosf(joints->y);
    float32 sy = sinf(joints->y);
    float32 cz = cosf(joints->z);
    float32 sz = sinf(joints->z);

    endEffector->x = cx * (l2 * cy + l3 * cy * cz) - l3 * sx * sz;
    endEffector->y = sx * (l2 * cy + l3 * cy * cz) + l3 * cx * sz;
    endEffector->z = l1 + l2 * sy + l3 * sy * cz;

    return endEffector;
}

bool inverseKinematics(Vector3D* joints, Vector3D* target)
{
    // Simplified inverse kinematics using geometric approach
    float32 l1 = 1.0f;
    float32 l2 = 1.0f;
    float32 l3 = 1.0f;

    // Calculate first joint angle (base rotation)
    joints->x = atan2f(target->y, target->x);

    // Calculate second and third joint angles using cosine law
    float r = sqrtf(target->x * target->x + target->y * target->y);
    float z = target->z - l1;

    float d = sqrtf(r * r + z * z);
    if(d > (l2 + l3))
        return false; // Target unreachable

    float a2 = acosf((l2 * l2 + d * d - l3 * l3)/(2 * l2 * d));
    float a1 = atan2f(z, r);

    joints->y = a1 + a2;
    joints->z = acosf((l2 * l2 + l3 * l3 - d * d)/(2 * l2 * l3));

    return true;
}

Quaternion* quaternionMult(Quaternion* q1, Quaternion* q2)
{
    Quaternion* result;

    result->w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
    result->x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
    result->y = q1->w * q2->y - q1->x * q2->z + q1->y * q2->w + q1->z * q2->x;
    result->z = q1->w * q2->z + q1->x * q2->y - q1->y * q2->x + q1->z * q2->w;

    return result;
}

Vector3D* quaternionToEuler(Quaternion* quaternion)
{
    Vector3D* euler;

    euler->x = atan2f(2 * (quaternion->w * quaternion->x + quaternion->y * quaternion->z), 1 - 2 * (quaternion->x * quaternion->x + quaternion->y * quaternion->y));
    euler->y = asinf(2 * (quaternion->w * quaternion->y - quaternion->z * quaternion->x));
    euler->z = atan2f(2 * (quaternion->w * quaternion->z + quaternion->x * quaternion->y), 1 - 2 * (quaternion->y * quaternion->y + quaternion->z * quaternion->z));

    return euler;
}

Quaternion* eulerToQuaternion(Vector3D* euler)
{
    Quaternion* quaternion;

    quaternion->w = cosf(euler->x / 2) * cosf(euler->y / 2) * cosf(euler->z / 2) + sinf(euler->x / 2) * sinf(euler->y / 2) * sinf(euler->z / 2);
    quaternion->x = sinf(euler->x / 2) * cosf(euler->y / 2) * cosf(euler->z / 2) - cosf(euler->x / 2) * sinf(euler->y / 2) * sinf(euler->z / 2);
    quaternion->y = cosf(euler->x / 2) * sinf(euler->y / 2) * cosf(euler->z / 2) + sinf(euler->x / 2) * cosf(euler->y / 2) * sinf(euler->z / 2);
    quaternion->z = cosf(euler->x / 2) * cosf(euler->y / 2) * sinf(euler->z / 2) - sinf(euler->x / 2) * sinf(euler->y / 2) * cosf(euler->z / 2);

    return quaternion;
}

#endif // _CORE_CONTROLLER_KINEMATICS_C_
