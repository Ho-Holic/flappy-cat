#ifndef FLAPPY_CAT_ANDROIDRECTANGLESHAPE_H
#define FLAPPY_CAT_ANDROIDRECTANGLESHAPE_H

// engine
#include <core/Shape.h>
#include <prototype/RectangleGeometry.h>
#include <prototype/FlatTransformation.h>
#include <prototype/VertexBasedRender.h>

class RectangleShape : public Shape {
public:
  RectangleShape(const Position& position, const Position& size);
  RectangleShape();

public:
  void setColor(const Color& color);
  const Color& color() const;

public:
  virtual RectangleGeometry& geometry() override;
  virtual FlatTransformation& transformation() override;
  virtual VertexBasedRender& render() override;

  virtual const RectangleGeometry& geometry() const override;
  virtual const FlatTransformation& transformation() const override;
  virtual const VertexBasedRender& render() const override;

private:
  void update();

private:
  FlatTransformation mTransformation;
  RectangleGeometry mGeometry;
  VertexBasedRender mRender;
};


#endif //FLAPPY_CAT_ANDROIDRECTANGLESHAPE_H
