
// engine
#include "VertexBasedRender.hpp"
#include <core/Window.hpp>
#include <core/Log.hpp>

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
    float angle = shape.transformation().rotation() * pi / 180.f;

    float sinValue = std::sin(angle);
    float cosValue = std::cos(angle);

    Position p = shape.geometry().pointAt(index) - shape.transformation().origin();

    float rotatedX = p.x() * cosValue - p.y() * sinValue;
    float rotatedY = p.x() * sinValue + p.y() * cosValue;

    /** TODO: add scale/origin later
     *
     * When object is moved, origin doesn't take into account
     * only for rotation.
     *
     * Scale is implemented only for 'View' to change all objects
     * representation on the screen, but local scale is not implemented
     */

    mVertices << Vertex(shape.transformation().position()
                        + Position(rotatedX, rotatedY)
                        + shape.transformation().origin(),
                        mBrushColor);
  }

}

const Color& VertexBasedRender::getBrushColor() const {
  return mBrushColor;
}
