
// self
#include "RectangleShape.h"

RectangleShape::RectangleShape(const Position& position, const Position& size)
: Shape()
, mTransform(position)
, mGeometry(size)
, mRender() {
  //
}

const Geometry& RectangleShape::geometry() const {
  return mGeometry;
}

const Transform& RectangleShape::transform() const {
  return mTransform;
}

const Render& RectangleShape::render() const {
  return mRender;
}







