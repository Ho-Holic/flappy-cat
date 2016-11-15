#ifndef FLAPPY_CAT_VERTEX_H
#define FLAPPY_CAT_VERTEX_H

// self
#include "Color.h"
#include "Position.h"

class Vertex {
public:
  Vertex(const Position& position, const Color& color);
  Vertex();

public:
  const Position& position() const;
  const Color& color() const;

private:
  Position mPosition;
  Color mColor;
};

#endif //FLAPPY_CAT_VERTEX_H
