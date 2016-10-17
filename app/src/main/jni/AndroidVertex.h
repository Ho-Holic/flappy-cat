#ifndef FLAPPY_CAT_VERTEX_H
#define FLAPPY_CAT_VERTEX_H

// self
#include "AndroidColor.h"
#include "core/Position.h"

class AndroidVertex {
public:
  AndroidVertex(const Position& position, const AndroidColor& color);

public:
  const Position& position() const;
  const AndroidColor& color() const;

private:
  Position mPosition;
  AndroidColor mColor;
};

#endif //FLAPPY_CAT_VERTEX_H
