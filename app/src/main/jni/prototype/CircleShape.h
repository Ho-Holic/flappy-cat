#ifndef FLAPPY_CAT_ANDROIDCIRCLESHAPE_H
#define FLAPPY_CAT_ANDROIDCIRCLESHAPE_H

// self
#include <core/Shape.h>
#include <prototype/CircleGeometry.h>
#include <prototype/FlatTransform.h>
#include <prototype/VertexBasedRender.h>

class CircleShape : public Shape {
public:
  CircleShape(const Position& position, float radius, std::size_t resolution);

public:
  virtual const Geometry& geometry() const;
  virtual const Transform& transform() const;
  virtual const Render& render() const;

private:
  FlatTransform mTransform;
  CircleGeometry mGeometry;
  VertexBasedRender mRender;
};


#endif //FLAPPY_CAT_ANDROIDCIRCLESHAPE_H
