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
  virtual const Geometry& geometry() const;
  virtual const Transform& transform() const;
  virtual const Render& render() const;

private:
  FlatTransform mTransform;
  RectangleGeometry mGeometry;
  VertexBasedRender mRender;
};


#endif //FLAPPY_CAT_ANDROIDRECTANGLESHAPE_H
