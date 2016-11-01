#ifndef FLAPPY_CAT_ANDROIDSHAPE_H
#define FLAPPY_CAT_ANDROIDSHAPE_H

// self
#include "Vertices.h"
#include "Geometry.h"
#include "Transform.h"

class Shape {
public:
  Shape();
  ~Shape() = default;

public:
  virtual const Geometry& geometry() const = 0;
  virtual const Transform& transform() const = 0;
};


#endif //FLAPPY_CAT_ANDROIDSHAPE_H
