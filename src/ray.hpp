#pragma once

#include "Vec3.hpp"

class Ray
{
public:
    Ray();
    Ray(const Vec3& origin, const Vec3& dir)
        : A(origin), B(dir) {}

    Vec3 origin() const { return A; }
    Vec3 direction() const { return B; }
    Vec3 point_at_parameter(float t) const { return A + t * B; }

    Vec3 A;
    Vec3 B;
};

