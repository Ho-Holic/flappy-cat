#ifndef FLAPPY_CAT_FLAPPYCATGROUND_H
#define FLAPPY_CAT_FLAPPYCATGROUND_H

// self
#include "FlappyCatEntity.h"
#include "FlappyCatSpike.h"
#include "FlappyCatChain.h"

// engine
#include <prototype/RectangleShape.h>

class FlappyCatFloor : public FlappyCatEntity{
public:
  FlappyCatFloor(const FlappyCatGameConstants& gameConstants);

public:
  const Shape& boundingBox() const;

public:
  virtual void initialize() override ;
  virtual void drawOn(const Window& window) const override;
  virtual const Position& position() const override;
  virtual void moveTo(const Position& position) override;
  virtual void setColor(const Color& color) override;
  virtual void update(const FrameDuration& time) override;
  virtual void resize(const Position& size) override;
  virtual void reset() override;

public:
  Position mPosition;
  Position mSize;
  Color mColor;
  RectangleShape mFloor;
  FlappyCatChain<FlappyCatSpike> mFloorSpikes;
  RectangleShape mBackgroundDirt;
};


#endif //FLAPPY_CAT_FLAPPYCATGROUND_H
