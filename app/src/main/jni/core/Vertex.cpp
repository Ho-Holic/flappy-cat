// self
#include "Vertex.h"

Vertex::Vertex(const Position& position,
                             const Color& color)
: mPosition(position)
, mColor(color) {
  //
}

const Position& Vertex::position() const {

  return mPosition;
}

const Color& Vertex::color() const {

  return mColor;
}








