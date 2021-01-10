// engine
#include "TriangleShape.hpp"

TriangleShape::TriangleShape(const Position& position, const Position& size)
: Shape()
, mTransformation(position)
, mGeometry(size)
, mRender() {
  mGeometry.onUpdate().connect(std::bind(&TriangleShape::update, this));
  mTransformation.onUpdate().connect(std::bind(&TriangleShape::update, this));
  update();
}

TriangleShape::TriangleShape()
: TriangleShape(Position(), Position()) {
  //
}

void TriangleShape::setColor(const Color& color) {

  render().setBrushColor(color);
  /* TODO: Create loop for coloring
   * Remove this 'update' and add 'foreach' to render and set correct color for vertex
   * update takes extra time to update position that does not changed
   */
  update();
}

TriangleGeometry& TriangleShape::geometry() {
  return mGeometry;
}

FlatTransformation& TriangleShape::transformation() {
  return mTransformation;
}

VertexBasedRender& TriangleShape::render() {
  return mRender;
}

const TriangleGeometry& TriangleShape::geometry() const {
  return mGeometry;
}

const FlatTransformation& TriangleShape::transformation() const {
  return mTransformation;
}

const VertexBasedRender& TriangleShape::render() const {
  return mRender;
}

void TriangleShape::update() {
  render().update(*this);
}
