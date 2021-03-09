#pragma once

#include "vec3.hpp"

// clang-format off
struct mat3 {
    float e0{1}; float e1{0}; float e2{0};
    float e3{0}; float e4{1}; float e5{0};
    float e6{0}; float e7{0}; float e8{1};
};

inline vec3 operator*(const mat3& a, const vec3& b)
{    
    return {
        a.e0 * b.x + a.e1 * b.y + a.e2 * b.z,
        a.e3 * b.x + a.e4 * b.y + a.e5 * b.z,
        a.e6 * b.x + a.e7 * b.y + a.e8 * b.z
    };    
}

inline mat3 operator*(const mat3& a, const mat3& b)
{
    return {
        a.e0 * b.e0 + a.e1 * b.e3 + a.e2 * b.e6,   a.e0 * b.e1 + a.e1 * b.e4 + a.e2 * b.e7,   a.e0 * b.e2 + a.e1 * b.e5 + a.e2 * b.e8,
        a.e3 * b.e0 + a.e4 * b.e3 + a.e5 * b.e6,   a.e3 * b.e1 + a.e4 * b.e4 + a.e5 * b.e7,   a.e3 * b.e2 + a.e4 * b.e5 + a.e5 * b.e8,
        a.e6 * b.e0 + a.e7 * b.e3 + a.e8 * b.e6,   a.e6 * b.e1 + a.e7 * b.e4 + a.e8 * b.e7,   a.e6 * b.e2 + a.e7 * b.e5 + a.e8 * b.e8,
    };

}
// clang-format on
