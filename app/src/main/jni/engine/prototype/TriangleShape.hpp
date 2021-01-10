#ifndef FLAPPY_CAT_TRIANGLESHAPE_H
#define FLAPPY_CAT_TRIANGLESHAPE_H

// engine
#include <core/Shape.hpp>
#include <prototype/TriangleGeometry.hpp>
#include <prototype/FlatTransformation.hpp>
#include <prototype/VertexBasedRender.hpp>

class TriangleShape : public Shape  {
public:
  // TODO: only right triangle now, later add tilt angle
  TriangleShape(const Position& position, const Position& size);
  TriangleShape();

public:
  void setColor(const Color& color);

public:
  virtual TriangleGeometry& geometry() override;
  virtual FlatTransformation& transformation() override;
  virtual VertexBasedRender& render() override;

  virtual const TriangleGeometry& geometry() const override;
  virtual const FlatTransformation& transformation() const override;
  virtual const VertexBasedRender& render() const override;

private:
  void update();

private:
  FlatTransformation mTransformation;
  TriangleGeometry mGeometry;
  VertexBasedRender mRender;
};


#endif //FLAPPY_CAT_TRIANGLESHAPE_H
