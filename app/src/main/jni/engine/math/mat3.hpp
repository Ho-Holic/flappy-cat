#pragma once

#include "vec3.hpp"

// clang-format off
struct mat3 {
    float e0{1}; float e1{0}; float e2{0};
    float e3{0}; float e4{1}; float e5{0};
    float e6{0}; float e7{0}; float e8{1};
};
// clang-format on

inline vec3 operator*(const mat3& a, const vec3& b)
{

    // clang-format off
    return {
        a.e0 * b.x + a.e1 * b.y + a.e2 * b.z,
        a.e3 * b.x + a.e4 * b.y + a.e5 * b.z,
        a.e6 * b.x + a.e7 * b.y + a.e8 * b.z
    };
    // clang-format on
}
