#pragma once

#include "vec3.hpp"

class ray
{
public:
    ray();
    ray(const vec3& origin, const vec3& dir)
        : A(origin), B(dir) {}

    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 point_at_parameter(float t) const { return A + t * B; }

    vec3 A;
    vec3 B;
};

