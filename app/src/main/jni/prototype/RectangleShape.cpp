
// self
#include "RectangleShape.h"

RectangleShape::RectangleShape(const Position& position, const Position& size)
: Shape()
, mTransform(position)
, mGeometry(size)
, mRender() {
  //
}

Geometry& RectangleShape::geometry() {
  return mGeometry;
}

Transform& RectangleShape::transform() {
  return mTransform;
}

Render& RectangleShape::render() {
  return mRender;
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













