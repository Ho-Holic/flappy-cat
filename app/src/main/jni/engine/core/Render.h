#ifndef FLAPPY_CAT_RENDER_H
#define FLAPPY_CAT_RENDER_H

#include <core/Transformation.h>

class Window;
class Shape;

class Render {
public:
  Render();
  virtual ~Render() = default;

public:
  virtual void update(const Shape& shape) = 0;
  virtual void drawOn(const Window& window, const Transformation& transformation) const = 0;
};


#endif //FLAPPY_CAT_RENDER_H
