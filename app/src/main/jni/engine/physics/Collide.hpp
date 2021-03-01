#pragma once

// engine
#include <core/Shape.hpp>

class Collide {
public:
    static bool circleRect(const vec2& circleCenter,
        float circleRadius,
        const Shape& rect);

    static bool pointRect(const vec2& p,
        const vec2& a,
        const vec2& b,
        const vec2& c,
        const vec2& d);

    static bool lineCircle(const vec2& circleCenter,
        float circleRadius,
        const vec2& a,
        const vec2& b);
};
