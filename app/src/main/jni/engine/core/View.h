#ifndef FLAPPY_CAT_VIEW_H
#define FLAPPY_CAT_VIEW_H

// engine
#include <core/Transformation.h>
#include <core/Signal.h>

class View : public Transformation {
public:
  View();
  virtual ~View() = default;

public:
  virtual void setOrigin(const Position& origin) override;
  // little hack here 'position' is 'size'
  virtual void setPosition(const Position& position) override;
  virtual void setScale(const Position& factor) override;
  virtual void setRotation(float angle) override;

  virtual const Position& origin() const override;
  virtual const Position& position() const override;
  virtual const Position& scale() const override;
  virtual float rotation() const override;
public:
  Position mOrigin;
  Position mSize;
  Position mScale;
  float mAngle;
};


#endif //FLAPPY_CAT_VIEW_H
