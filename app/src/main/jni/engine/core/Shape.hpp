#pragma once


// engine
#include <core/Vertices.hpp>
#include <core/Geometry.hpp>
#include <core/Transformation.hpp>
#include <core/Render.hpp>


class Geometry;
class Transformation;
class Render;

class Shape {
public:
  Shape();
  virtual ~Shape() = default;

public:
  virtual Geometry& geometry() = 0;
  virtual Transformation& transformation() = 0;
  virtual Render& render() = 0;

  virtual const Geometry& geometry() const = 0;
  virtual const Transformation& transformation() const = 0;
  virtual const Render& render() const = 0;
};



