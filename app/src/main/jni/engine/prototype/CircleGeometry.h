#ifndef FLAPPY_CAT_CIRCLEGEOMETRY_H
#define FLAPPY_CAT_CIRCLEGEOMETRY_H

// engine
#include <core/Geometry.h>
#include <core/Signal.h>

class CircleGeometry : public Geometry {
public:
  using OnUpdateSignal = Signal<void()>;

public:
  CircleGeometry(Position::value_type radius, std::size_t resolution);

public:
  OnUpdateSignal& onUpdate();
  void setResolution(std::size_t resolution);
  void setRadius(Position::value_type radius);
  Position::value_type radius() const;

public:
  virtual size_type points() const override;
  virtual Position pointAt(size_type index) const override;

private:
  Position::value_type mRadius;
  std::size_t mResolution;
  OnUpdateSignal mOnUpdate;
};


#endif //FLAPPY_CAT_CIRCLEGEOMETRY_H
