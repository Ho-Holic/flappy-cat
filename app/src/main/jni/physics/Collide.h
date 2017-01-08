#ifndef FLAPPY_CAT_COLLIDE_H
#define FLAPPY_CAT_COLLIDE_H

// self
#include <core/Shape.h>

class Collide {
public:
  static bool circleRect(const Position& circleCenter,
                         float circleRadius,
                         const Shape& rect);

  // replace Shape w/ TransformMatrix and operate with this structure
  // to eliminate code like `rect.transformation().position() + rect.geometry().pointAt(0)`
  static bool pointRect(const Position& p,
                        const Position& a,
                        const Position& b,
                        const Position& c,
                        const Position& d);

  static bool lineCircle(const Position& circleCenter,
                         float circleRadius,
                         const Position& a,
                         const Position& b);
  };


#endif //FLAPPY_CAT_COLLIDE_H
