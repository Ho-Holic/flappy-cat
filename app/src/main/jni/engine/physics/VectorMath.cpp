// engine
#include "VectorMath.h"

// stl
#include <cmath>
#include <algorithm>

Position::value_type VectorMath::dot(const Position& a, const Position& b) {

  return a.x() * b.x() + a.y() * b.y();
}

Position::value_type VectorMath::distance(const Position& a, const Position& b) {
  return std::sqrt((a.x() - b.x()) * (a.x() - b.x())
                 + (a.y() - b.y()) * (a.y() - b.y()));
}

Position VectorMath::projectionPointLine(const Position& p, const Position& a, const Position& b) {

  Position c = b - a;
  Position::value_type factor = VectorMath::dot(c, p-a) / (c.x() * c.x() + c.y() * c.y());

  return (c * factor) + a; // result is projection of 'p' on 'ab'
}





