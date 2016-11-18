// self
#include "CircleShape.h"

CircleShape::CircleShape(const Position& position, float radius, std::size_t resolution)
: Shape()
, mTransformation(position)
, mGeometry(radius, resolution)
, mRender() {
  mGeometry.onUpdate().connect(std::bind(&CircleShape::update, this));
  mTransformation.onUpdate().connect(std::bind(&CircleShape::update, this));
  update();
}

CircleGeometry& CircleShape::geometry() {
  return mGeometry;
}

FlatTransformation& CircleShape::transformation() {
  return mTransformation;
}

VertexBasedRender& CircleShape::render() {
  return mRender;
}

const CircleGeometry& CircleShape::geometry() const {
  return mGeometry;
}

const FlatTransformation& CircleShape::transformation() const {
  return mTransformation;
}

const VertexBasedRender& CircleShape::render() const {
  return mRender;
}

void CircleShape::update() {
  render().update(*this);
}















