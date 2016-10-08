#ifndef FLAPPY_CAT_VERTEX_H
#define FLAPPY_CAT_VERTEX_H

// self
#include "AndroidColor.h"
#include "AndroidPosition.h"

class AndroidVertex {
public:
  AndroidVertex(const AndroidPosition& position, const AndroidColor& color);

public:
  const AndroidPosition& position() const;
  const AndroidColor& color() const;

private:
  AndroidPosition mPosition;
  AndroidColor mColor;
};

#endif //FLAPPY_CAT_VERTEX_H
