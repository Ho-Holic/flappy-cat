#ifndef FLAPPY_CAT_FLATTRANSFROM_H
#define FLAPPY_CAT_FLATTRANSFROM_H

// self
#include <core/Transformation.h>
#include <core/Signal.h>

class FlatTransformation : public Transformation {
public:
  using OnUpdateSignal = Signal<void()>;

public:
  FlatTransformation(const Position& position);
  FlatTransformation();

public:
  OnUpdateSignal& onUpdate();

public:
  virtual void setPosition(const Position& position) override;
  virtual const Position& getPosition() const override;

private:
  Position mPosition;
  OnUpdateSignal mOnUpdate;
};


#endif //FLAPPY_CAT_FLATTRANSFROM_H
