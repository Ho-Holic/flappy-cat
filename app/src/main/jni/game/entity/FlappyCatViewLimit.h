#ifndef FLAPPY_CAT_FLAPPYCATVIEWLIMIT_H
#define FLAPPY_CAT_FLAPPYCATVIEWLIMIT_H

// engine
#include <prototype/RectangleShape.h>

// game
#include "FlappyCatEntity.h"

class FlappyCatViewLimit : public FlappyCatEntity {
public:
  FlappyCatViewLimit(const FlappyCatGameConstants& gameConstants);

public:
  virtual void drawOn(const Window& window) const override;
  virtual void moveTo(const Position& position) override;
  virtual void resize(const Position& size) override;
  virtual const Position& position() const override;

private:
  void syncChildren();

private:
  Position mPosition;
  Position mSize;
  RectangleShape mTop;
  RectangleShape mTopRight;
  RectangleShape mRight;
  RectangleShape mBottomRight;
  RectangleShape mBottom;
  RectangleShape mBottomLeft;
  RectangleShape mLeft;
  RectangleShape mTopLeft;
};


#endif //FLAPPY_CAT_FLAPPYCATVIEWLIMIT_H
