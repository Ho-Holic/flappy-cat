
// self
#include "VertexBasedRender.h"
#include <core/Window.h>

VertexBasedRender::VertexBasedRender()
: Render()
, mVertices()
, mBrushColor() {
  //
}

void VertexBasedRender::setBrushColor(const Color& color) {

  mBrushColor = color;
}

void VertexBasedRender::drawOn(const Window& window, const Transformation& transformation) const {

  window.drawVertices(mVertices, transformation);
}

void VertexBasedRender::update(const Shape& shape) {

  Geometry::size_type points = shape.geometry().points();

  // TODO: not optimal, create more clever approach later
  mVertices.reset();

  if (points <3) { // give me some love <3
    return;
  }

  for (Geometry::size_type index = 0; index < points; ++index) {

    mVertices << Vertex(shape.transformation().position() + shape.geometry().pointAt(index),
                        mBrushColor);
  }

}
