#ifndef FLAPPY_CAT_RECTANGLEGEOMETRY_H
#define FLAPPY_CAT_RECTANGLEGEOMETRY_H

// self
#include <core/Geometry.h>
#include <core/Signal.h>

class RectangleGeometry : public Geometry {
public:
  using OnUpdateSignal = Signal<void()>;

public:
  RectangleGeometry(const Position& size);

public:
  OnUpdateSignal& onUpdate();
  void resize(const Position& size);
  const Position& size() const;

public:
  virtual size_type points() const override;
  virtual Position pointAt(size_type index) const override;

private:
  Position mSize;
  OnUpdateSignal mOnUpdate;
};


#endif //FLAPPY_CAT_RECTANGLEGEOMETRY_H
