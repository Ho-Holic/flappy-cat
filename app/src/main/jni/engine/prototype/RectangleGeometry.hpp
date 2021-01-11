#pragma once


// engine
#include <core/Geometry.hpp>
#include <core/Signal.hpp>

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



