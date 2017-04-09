
// engine
#include "VertexBasedRender.h"
#include <core/Window.h>
#include <core/Log.h>

// stl
#include <cmath>

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

    constexpr float pi = 3.141592654f;

    // TODO: remove this part and make transform matrix
    // rotate
    Position::value_type angle = shape.transformation().rotation() * pi / 180.f;

    Position::value_type sinValue = std::sin(angle);
    Position::value_type cosValue = std::cos(angle);

    Position p = shape.geometry().pointAt(index) - shape.transformation().origin();

    Position::value_type rotatedX = p.x() * cosValue - p.y() * sinValue;
    Position::value_type rotatedY = p.x() * sinValue + p.y() * cosValue;

    // TODO: add shape scale
    mVertices << Vertex(shape.transformation().position()
                        + Position(rotatedX, rotatedY)
                        + shape.transformation().origin(),
                        mBrushColor);
  }

}
