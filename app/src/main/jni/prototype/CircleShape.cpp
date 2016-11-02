// self
#include "CircleShape.h"

CircleShape::CircleShape(const Position& position, float radius, std::size_t resolution)
: Shape()
, mTransform(position)
, mGeometry(radius, resolution)
, mRender() {
  //
}

const Geometry& CircleShape::geometry() const {
  return mGeometry;
}

const Transform& CircleShape::transform() const {
  return mTransform;
}

const Render& CircleShape::render() const {
  return mRender;
}







