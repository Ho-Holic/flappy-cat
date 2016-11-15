
// self
#include "CircleGeometry.h"

// stl
#include <cmath>

CircleGeometry::CircleGeometry(float radius, std::size_t resolution)
: Geometry()
, mRadius(radius)
, mResolution(resolution) {
  //
}

Geometry::size_type CircleGeometry::points() const {
  return mResolution;
}

Position CircleGeometry::pointAt(size_type index) const {

  constexpr float pi = 3.141592654f;

  float angle = index * 2.f * pi / mResolution - pi / 2.f;
  float x = std::cos(angle) * mRadius;
  float y = std::sin(angle) * mRadius;

  return Position(mRadius + x, mRadius + y);
}







