
// self
#include "RectangleShape.h"
#include "Log.h"

// stl
#include <functional>

RectangleShape::RectangleShape(const Position& position, const Position& size)
: Shape()
, mTransform(position)
, mGeometry(size)
, mRender() {
  mGeometry.onUpdate().connect(std::bind(&RectangleShape::update, this));
  update();
}

RectangleGeometry& RectangleShape::geometry() {
  return mGeometry;
}

FlatTransform& RectangleShape::transform() {
  return mTransform;
}

VertexBasedRender& RectangleShape::render() {
  return mRender;
}

const RectangleGeometry& RectangleShape::geometry() const {
  return mGeometry;
}

const FlatTransform& RectangleShape::transform() const {
  return mTransform;
}

const VertexBasedRender& RectangleShape::render() const {
  return mRender;
}

void RectangleShape::update() {
  render().update(*this);
}















