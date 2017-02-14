#ifndef FLAPPY_CAT_VECTORMATH_H
#define FLAPPY_CAT_VECTORMATH_H

// self
#include <core/Position.h>

class VectorMath {
public:
  static Position::value_type dot(const Position& a, const Position& b);
  static Position::value_type distance(const Position& a, const Position& b);
  static Position projectionPointLine(const Position& p, const Position& a, const Position& b);
};


#endif //FLAPPY_CAT_VECTORMATH_H
