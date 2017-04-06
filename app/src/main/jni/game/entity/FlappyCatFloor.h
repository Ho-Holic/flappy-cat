#ifndef FLAPPY_CAT_FLAPPYCATGROUND_H
#define FLAPPY_CAT_FLAPPYCATGROUND_H

// game
#include "FlappyCatEntity.h"
#include "FlappyCatSpike.h"
#include "FlappyCatChain.h"

// engine
#include <prototype/RectangleShape.h>

class FlappyCatFloor : public FlappyCatEntity {
public:
  using entity_type = FlappyCatFloor;
  using modifier_type = std::function<void(entity_type&)>;
  using update_modifier_type = std::function<void(entity_type&, const FrameDuration& time)>;
public:
  FlappyCatFloor(const FlappyCatGameConstants& gameConstants);

public:
  const RectangleShape& boundingBox() const;

public:
  virtual void initialize() override ;
  virtual void drawOn(const Window& window) const override;
  virtual const Position& position() const override;
  virtual void moveTo(const Position& position) override;
  virtual void update(const FrameDuration& time) override;
  virtual void resize(const Position& size) override;
  virtual void reset() override;

public:
  void setColor(const Color& floorColor, const Color& dirtColor);
  void setResetModifier(const modifier_type& modifier);
  void setUpdateModifier(const update_modifier_type& modifier);
  void setMovementDisplacement(const Position& movementDisplacement);

private:
  void syncChildren();

private:
  Position mPosition;
  Position mSize;
  RectangleShape mFloor;
  FlappyCatChain<FlappyCatSpike> mFloorSpikes;
  RectangleShape mBackgroundDirt;
  modifier_type mResetModifier;
  update_modifier_type mUpdateModifier;
};


#endif //FLAPPY_CAT_FLAPPYCATGROUND_H