#ifndef FLAPPY_CAT_COLLIDE_H
#define FLAPPY_CAT_COLLIDE_H

// engine
#include <core/Shape.hpp>

class Collide {
public:
  static bool circleRect(const Position& circleCenter,
                         float circleRadius,
                         const Shape& rect);

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
