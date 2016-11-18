#ifndef FLAPPY_CAT_ANDROIDSHAPE_H
#define FLAPPY_CAT_ANDROIDSHAPE_H

// self
#include <core/Vertices.h>
#include <core/Geometry.h>
#include <core/Transformation.h>
#include <core/Render.h>



class Shape {
public:
  Shape();
  ~Shape() = default;

public:
  virtual Geometry& geometry() = 0;
  virtual Transformation& transform() = 0;
  virtual Render& render() = 0;

  virtual const Geometry& geometry() const = 0;
  virtual const Transformation& transform() const = 0;
  virtual const Render& render() const = 0;
};


#endif //FLAPPY_CAT_ANDROIDSHAPE_H
