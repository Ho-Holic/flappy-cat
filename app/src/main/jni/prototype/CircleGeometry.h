#ifndef FLAPPY_CAT_CIRCLEGEOMETRY_H
#define FLAPPY_CAT_CIRCLEGEOMETRY_H

// self
#include <core/Geometry.h>

class CircleGeometry : public Geometry {
public:
  CircleGeometry(float radius, std::size_t resolution);

public:
  virtual size_type points() const override;
  virtual Position pointAt(size_type index) const override;
private:
  float mRadius;
  std::size_t mResolution;
};


#endif //FLAPPY_CAT_CIRCLEGEOMETRY_H
