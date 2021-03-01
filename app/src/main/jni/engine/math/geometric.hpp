#pragma once

#include <math/vec2.hpp>

float dot(const vec2& a, const vec2& b);
float distance(const vec2& a, const vec2& b);
vec2 projectionPointLine(const vec2& p, const vec2& a, const vec2& b);

template <typename T>
inline T linearInterpolation(const T& x, const T& x0, const T& x1,
    const T& y0, const T& y1);

template <typename T>
T linearInterpolation(const T& x, const T& x0, const T& x1,
    const T& y0, const T& y1)
{
    return y0 + (y1 - y0) * ((x - x0) / (x1 - x0));
}
