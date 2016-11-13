#ifndef FLAPPY_CAT_WINDOW_H
#define FLAPPY_CAT_WINDOW_H

// self
#include <core/Color.h>
#include <core/Shape.h>

class Window {
public:
  Window();
  virtual ~Window() = default;

public:
  virtual void clear(const Color& color) const = 0;
  virtual void draw(const Shape& shape) const = 0;
  virtual void drawVertices(const Vertices& vertices) const = 0;
};


#endif //FLAPPY_CAT_WINDOW_H
