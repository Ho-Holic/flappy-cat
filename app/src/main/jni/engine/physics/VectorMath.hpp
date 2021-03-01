#pragma once

// engine
#include <math/vec2.hpp>

class VectorMath {
public:
    static float dot(const vec2& a, const vec2& b);
    static float distance(const vec2& a, const vec2& b);
    static vec2 projectionPointLine(const vec2& p, const vec2& a, const vec2& b);

    template <typename T>
    static T linearInterpolation(const T& x, const T& x0, const T& x1,
        const T& y0, const T& y1);
};

template <typename T>
T VectorMath::linearInterpolation(const T& x, const T& x0, const T& x1,
    const T& y0, const T& y1)
{
    return y0 + (y1 - y0) * ((x - x0) / (x1 - x0));
}
