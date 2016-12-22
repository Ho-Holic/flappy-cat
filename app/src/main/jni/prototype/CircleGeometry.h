#ifndef FLAPPY_CAT_CIRCLEGEOMETRY_H
#define FLAPPY_CAT_CIRCLEGEOMETRY_H

// self
#include <core/Geometry.h>
#include <core/Signal.h>

class CircleGeometry : public Geometry {
public:
  using OnUpdateSignal = Signal<void()>;

public:
  CircleGeometry(float radius, std::size_t resolution);

public:
  OnUpdateSignal& onUpdate();
  void setResolution(std::size_t resolution);
  void setRadius(float radius);
  float radius() const;

public:
  virtual size_type points() const override;
  virtual Position pointAt(size_type index) const override;

private:
  float mRadius;
  std::size_t mResolution;
  OnUpdateSignal mOnUpdate;
};


#endif //FLAPPY_CAT_CIRCLEGEOMETRY_H
