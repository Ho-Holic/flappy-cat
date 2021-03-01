// engine
#include "Collide.hpp"
#include <core/Log.hpp>
#include <physics/VectorMath.hpp>

// style
#include <style/Guidelines.hpp>

// stl
#include <algorithm>

bool Collide::circleRect(const vec2& circleCenter,
    float circleRadius,
    const Shape& rect)
{

    // TODO: actually algorithm can ran on any convex polygon, just need to generalize it

    REQUIRE(TAG, rect.geometry().points() == 4, "Rect must have four points");

    vec2 a = rect.transformation().position() + rect.geometry().pointAt(0);
    vec2 b = rect.transformation().position() + rect.geometry().pointAt(1);
    vec2 c = rect.transformation().position() + rect.geometry().pointAt(2);
    vec2 d = rect.transformation().position() + rect.geometry().pointAt(3);

    return pointRect(circleCenter, a, b, c, d)
        || lineCircle(circleCenter, circleRadius, a, b)
        || lineCircle(circleCenter, circleRadius, b, c)
        || lineCircle(circleCenter, circleRadius, c, d)
        || lineCircle(circleCenter, circleRadius, d, a);
}

bool Collide::pointRect(const vec2& p,
    const vec2& a,
    const vec2& b,
    const vec2& c,
    const vec2& d)
{

    UNUSED(c); // algorithm don't use 'c' point to find intersection

    auto apab = VectorMath::dot(p - a, b - a);
    auto ab2 = VectorMath::dot(b - a, b - a);
    auto apad = VectorMath::dot(p - a, d - a);
    auto ad2 = VectorMath::dot(d - a, d - a);

    return (0 <= apab && apab <= ab2) && (0 <= apad && apad <= ad2);
}

bool Collide::lineCircle(const vec2& circleCenter, float circleRadius,
    const vec2& a,
    const vec2& b)
{

    vec2 c = VectorMath::projectionPointLine(circleCenter, a, b);

    auto distanceAB = VectorMath::distance(a, b);
    auto distanceAC = VectorMath::distance(a, c);
    auto distanceCB = VectorMath::distance(c, b);

    bool isPointOnLine = distanceAC + distanceCB <= distanceAB; // insure we inside a line

    /*
   * TODO: Fix bug with intersection between very big circle
   *
   * If circle is very big compared to line 'ab', collide would fail
   * For example consider line segment inside the circle but projected point is outside of
   * this line segment, but we still in the circle yet =)
   */

    return isPointOnLine && (VectorMath::distance(circleCenter, c) <= circleRadius);
}
