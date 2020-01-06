
// engine
#include "CircleGeometry.h"

// stl
#include <cmath>

CircleGeometry::CircleGeometry(f32 radius, std::size_t resolution)
: Geometry()
, mRadius(radius)
, mResolution(resolution)
, mOnUpdate() {
  //
}

Geometry::size_type CircleGeometry::points() const {

  return mResolution;
}

Position CircleGeometry::pointAt(size_type index) const {

  constexpr f32 pi = 3.141592654f;

  f32 angle = index * 2.f * pi / mResolution - pi / 2.f;
  f32 x = std::cos(angle) * mRadius;
  f32 y = std::sin(angle) * mRadius;

  return Position(mRadius + x, mRadius + y);
}

CircleGeometry::OnUpdateSignal& CircleGeometry::onUpdate() {

  return mOnUpdate;
}

void CircleGeometry::setResolution(std::size_t resolution) {

  mResolution = resolution;
  mOnUpdate.emit();
}

void CircleGeometry::setRadius(f32 radius) {

  mRadius = radius;
  mOnUpdate.emit();
}

f32 CircleGeometry::radius() const {

  return mRadius;
}















