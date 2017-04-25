#ifndef FLAPPY_CAT_ANDROIDCIRCLESHAPE_H
#define FLAPPY_CAT_ANDROIDCIRCLESHAPE_H

// engine
#include <core/Shape.h>
#include <prototype/CircleGeometry.h>
#include <prototype/FlatTransformation.h>
#include <prototype/VertexBasedRender.h>

class CircleShape : public Shape {
public:
  CircleShape(const Position& position, Position::value_type radius, std::size_t resolution);
  CircleShape();

public:
  void setColor(const Color& color);

public:
  virtual CircleGeometry& geometry() override;
  virtual FlatTransformation& transformation() override;
  virtual VertexBasedRender& render() override;

  virtual const CircleGeometry& geometry() const override;
  virtual const FlatTransformation& transformation() const override;
  virtual const VertexBasedRender& render() const override;

private:
  void update();

private:
  FlatTransformation mTransformation;
  CircleGeometry mGeometry;
  VertexBasedRender mRender;
  Color mColor;
};


#endif //FLAPPY_CAT_ANDROIDCIRCLESHAPE_H
