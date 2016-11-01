#ifndef FLAPPY_CAT_GEOMETRY_H
#define FLAPPY_CAT_GEOMETRY_H

// stl
#include <cstdint>

// self
#include "Position.h"

class Geometry {
public:
  typedef std::size_t size_type;

public:
  virtual ~Geometry() = default;

public:
  virtual size_type pointSize() const = 0;
  virtual Position pointAt(size_type index) const = 0;
};


#endif //FLAPPY_CAT_GEOMETRY_H
