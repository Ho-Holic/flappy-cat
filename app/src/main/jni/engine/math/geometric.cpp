#include "geometric.hpp"
#include <algorithm>
#include <cmath>

float dot(const vec2& a, const vec2& b)
{
    return a.x() * b.x() + a.y() * b.y();
}

float distance(const vec2& a, const vec2& b)
{
    return std::sqrt((a.x() - b.x()) * (a.x() - b.x())
        + (a.y() - b.y()) * (a.y() - b.y()));
}

vec2 projectionPointLine(const vec2& p, const vec2& a, const vec2& b)
{
    vec2 c = b - a;
    float factor = dot(c, p - a) / (c.x() * c.x() + c.y() * c.y());

    return (c * factor) + a; // result is projection of 'p' on 'ab'
}
