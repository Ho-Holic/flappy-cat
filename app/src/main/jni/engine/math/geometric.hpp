#pragma once

#include <math/vec2.hpp>

float dot(const vec2& a, const vec2& b);
float distance(const vec2& a, const vec2& b);
vec2 projectionPointLine(const vec2& p, const vec2& a, const vec2& b);

inline float radians(float degrees) { return degrees * 0.01745329251994329576923690768489f; }
inline float degrees(float radians) { return radians * 57.295779513082320876798154814105f; }

template <typename T>
inline T linearInterpolation(const T& x, const T& x0, const T& x1,
    const T& y0, const T& y1);

template <typename T>
T linearInterpolation(const T& x, const T& x0, const T& x1,
    const T& y0, const T& y1)
{
    return y0 + (y1 - y0) * ((x - x0) / (x1 - x0));
}
