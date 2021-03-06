
// engine
#include "RectangleShape.h"
#include <core/Log.h>

// stl
#include <functional>

RectangleShape::RectangleShape(const Position& position, const Position& size)
: Shape()
, mTransformation(position)
, mGeometry(size)
, mRender() {
  mGeometry.onUpdate().connect(std::bind(&RectangleShape::update, this));
  mTransformation.onUpdate().connect(std::bind(&RectangleShape::update, this));
  update();
}

RectangleShape::RectangleShape()
: RectangleShape(Position(), Position()) {
  //
}

void RectangleShape::setColor(const Color& color) {

  render().setBrushColor(color);
  /* TODO: Create loop for coloring
   * Remove this 'update' and add 'foreach' to render and set correct color for vertex
   * update takes extra time to update position that does not changed
   */
  update();
}

RectangleGeometry& RectangleShape::geometry() {
  return mGeometry;
}

FlatTransformation& RectangleShape::transformation() {
  return mTransformation;
}

VertexBasedRender& RectangleShape::render() {
  return mRender;
}

const RectangleGeometry& RectangleShape::geometry() const {
  return mGeometry;
}

const FlatTransformation& RectangleShape::transformation() const {
  return mTransformation;
}

const VertexBasedRender& RectangleShape::render() const {
  return mRender;
}

void RectangleShape::update() {
  render().update(*this);
}


