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
  virtual Geometry& geometry() override;
  virtual Transform& transform() override;
  virtual Render& render() override;

  virtual const Geometry& geometry() const override;
  virtual const Transform& transform() const override;
  virtual const Render& render() const override;

private:
  FlatTransform mTransform;
  CircleGeometry mGeometry;
  VertexBasedRender mRender;
};


#endif //FLAPPY_CAT_ANDROIDCIRCLESHAPE_H
