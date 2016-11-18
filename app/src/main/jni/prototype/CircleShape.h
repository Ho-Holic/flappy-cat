#ifndef FLAPPY_CAT_ANDROIDCIRCLESHAPE_H
#define FLAPPY_CAT_ANDROIDCIRCLESHAPE_H

// self
#include <core/Shape.h>
#include <prototype/CircleGeometry.h>
#include <prototype/FlatTransformation.h>
#include <prototype/VertexBasedRender.h>

class CircleShape : public Shape {
public:
  CircleShape(const Position& position, float radius, std::size_t resolution);

public:
  virtual CircleGeometry& geometry() override;
  virtual FlatTransformation& transform() override;
  virtual VertexBasedRender& render() override;

  virtual const CircleGeometry& geometry() const override;
  virtual const FlatTransformation& transform() const override;
  virtual const VertexBasedRender& render() const override;

private:
  void update();

private:
  FlatTransformation mTransform;
  CircleGeometry mGeometry;
  VertexBasedRender mRender;
};


#endif //FLAPPY_CAT_ANDROIDCIRCLESHAPE_H
