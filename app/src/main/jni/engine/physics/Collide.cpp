// engine
#include "Collide.h"
#include <core/Log.h>
#include <physics/VectorMath.h>

// style
#include <style/Guidelines.h>

// stl
#include <algorithm>

bool Collide::circleRect(const Position& circleCenter,
                         f32 circleRadius,
                         const Shape& rect) {

  // TODO: actually algorithm can ran on any convex polygon, just need to generalize it

  REQUIRE(TAG, rect.geometry().points() == 4, "Rect must have four points");

  Position a = rect.transformation().position() + rect.geometry().pointAt(0);
  Position b = rect.transformation().position() + rect.geometry().pointAt(1);
  Position c = rect.transformation().position() + rect.geometry().pointAt(2);
  Position d = rect.transformation().position() + rect.geometry().pointAt(3);

  return pointRect (circleCenter, a, b, c, d)
      || lineCircle(circleCenter, circleRadius, a, b)
      || lineCircle(circleCenter, circleRadius, b, c)
      || lineCircle(circleCenter, circleRadius, c, d)
      || lineCircle(circleCenter, circleRadius, d, a);
}

bool Collide::pointRect(const Position& p,
                        const Position& a,
                        const Position& b,
                        const Position& c,
                        const Position& d) {

  UNUSED(c); // algorithm don't use 'c' point to find intersection

  auto apab = VectorMath::dot(p - a, b - a);
  auto ab2  = VectorMath::dot(b - a, b - a);
  auto apad = VectorMath::dot(p - a, d - a);
  auto ad2  = VectorMath::dot(d - a, d - a);

  return (0 <= apab && apab <= ab2) && (0 <= apad && apad <= ad2);
}

bool Collide::lineCircle(const Position& circleCenter, f32 circleRadius,
                         const Position& a,
                         const Position& b) {

  Position c = VectorMath::projectionPointLine(circleCenter, a, b);

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



