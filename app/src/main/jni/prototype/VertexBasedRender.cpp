
// self
#include "VertexBasedRender.h"
#include <core/Window.h>

VertexBasedRender::VertexBasedRender()
: Render()
, mVertices() {
  //
}

void VertexBasedRender::drawOn(const Window& window) const {

  window.drawVertices(mVertices);
}

void VertexBasedRender::update(const Shape& shape) {

  Geometry::size_type points = shape.geometry().points();

  // if not at least a triangle, reset and exit
  if (points < 3) {
    mVertices.reset();
    return;
  }

  for (Geometry::size_type index = 0; index < points; ++index) {

    mVertices << Vertex(shape.geometry().pointAt(index), Color(255, 0, 0));
  }

}





