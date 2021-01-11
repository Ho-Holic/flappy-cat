#pragma once


// engine
#include <core/Color.hpp>
#include <core/Shape.hpp>
#include <core/View.hpp>

class Window {
public:
  Window();
  virtual ~Window() = default;

public:
  virtual void clear(const Color& color) const = 0;
  virtual void draw(const Shape& shape) const = 0;
  virtual void drawVertices(const Vertices& vertices,
                            const Transformation& transformation) const = 0;
  virtual void display() const = 0;

public:
  const View& view() const;
  View& view();

private:
  View mView;
};



