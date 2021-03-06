#ifndef FLAPPY_CAT_TRIANGLEGEOMETRY_H
#define FLAPPY_CAT_TRIANGLEGEOMETRY_H

// engine
#include <core/Geometry.h>
#include <core/Signal.h>

class TriangleGeometry : public Geometry {
public:
  using OnUpdateSignal = Signal<void()>;

public:
  TriangleGeometry(const Position& size);

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


#endif //FLAPPY_CAT_TRIANGLEGEOMETRY_H
