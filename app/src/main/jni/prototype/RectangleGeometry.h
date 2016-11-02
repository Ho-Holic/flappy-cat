#ifndef FLAPPY_CAT_RECTANGLEGEOMETRY_H
#define FLAPPY_CAT_RECTANGLEGEOMETRY_H

// self
#include <core/Geometry.h>

class RectangleGeometry : public Geometry {
public:
  RectangleGeometry(const Position& size);

public:
  virtual size_type points() const override;
  virtual Position pointAt(size_type index) const override;

private:
  Position mSize;
};


#endif //FLAPPY_CAT_RECTANGLEGEOMETRY_H
