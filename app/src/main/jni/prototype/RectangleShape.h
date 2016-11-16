#ifndef FLAPPY_CAT_ANDROIDRECTANGLESHAPE_H
#define FLAPPY_CAT_ANDROIDRECTANGLESHAPE_H

// self
#include <core/Shape.h>
#include <prototype/RectangleGeometry.h>
#include <prototype/FlatTransform.h>
#include <prototype/VertexBasedRender.h>

class RectangleShape : public Shape {
public:
 RectangleShape(const Position& position, const Position& size);

public:
  virtual RectangleGeometry& geometry() override;
  virtual FlatTransform& transform() override;
  virtual VertexBasedRender& render() override;

  virtual const RectangleGeometry& geometry() const override;
  virtual const FlatTransform& transform() const override;
  virtual const VertexBasedRender& render() const override;

private:
  void update();

private:
  FlatTransform mTransform;
  RectangleGeometry mGeometry;
  VertexBasedRender mRender;
};


#endif //FLAPPY_CAT_ANDROIDRECTANGLESHAPE_H
