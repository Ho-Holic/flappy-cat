#ifndef FLAPPY_CAT_VECTORMATH_H
#define FLAPPY_CAT_VECTORMATH_H

// engine
#include <core/Position.hpp>

class VectorMath {
public:
  static float dot(const Position& a, const Position& b);
  static float distance(const Position& a, const Position& b);
  static Position projectionPointLine(const Position& p, const Position& a, const Position& b);

  template <typename T>
  static T linearInterpolation(const T& x, const T& x0, const T& x1,
                                           const T& y0, const T& y1);
};

template <typename T>
T VectorMath::linearInterpolation(const T& x, const T& x0, const T& x1,
                                              const T& y0, const T& y1) {
  return y0 + (y1 - y0) * ((x - x0)/(x1 - x0));
}


#endif //FLAPPY_CAT_VECTORMATH_H
