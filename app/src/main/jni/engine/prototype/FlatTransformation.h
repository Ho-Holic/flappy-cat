#ifndef FLAPPY_CAT_FLATTRANSFROM_H
#define FLAPPY_CAT_FLATTRANSFROM_H

// engine
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
  virtual const Position& origin() const override;
  virtual const Position& position() const override;
  virtual const Position& scale() const override;
  virtual Position::value_type rotation() const override;

  virtual void setOrigin(const Position& origin) override;
  virtual void setPosition(const Position& position) override;
  virtual void setScale(const Position& factor) override;
  virtual void setRotation(Position::value_type angle) override;
private:
  Position mPosition;
  Position mOrigin;
  Position mScale;
  Position::value_type mAngle;
  OnUpdateSignal mOnUpdate;
};


#endif //FLAPPY_CAT_FLATTRANSFROM_H
