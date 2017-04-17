#ifndef FLAPPY_CAT_FLAPPYCATHERO_H
#define FLAPPY_CAT_FLAPPYCATHERO_H

// engine
#include <prototype/CircleShape.h>

// game
#include "FlappyCatEntity.h"
#include "FlappyCatMascot.h"

class FlappyCatHero : public FlappyCatEntity {
public:
  using entity_type = FlappyCatHero;
  using modifier_type = std::function<void(entity_type&)>;
  using update_modifier_type = std::function<void(entity_type&, const FrameDuration& time)>;

public:
  FlappyCatHero(const FlappyCatGameConstants& gameConstants);

public:
  virtual void drawOn(const Window& window) const override;
  virtual void reset() override;
  virtual void update(const FrameDuration& time) override;

public:
  void setColor(const Color& backgroundColor,
                const Color& bodyColor,
                const Color& scarfColor,
                const Color& mouthColor);

  void setResetModifier(const modifier_type& modifier);
  void setUpdateModifier(const update_modifier_type& modifier);

  void setRadius(Position::value_type radius);
  Position::value_type radius() const;

  void setJumpConstants(const Position& acceleration, const Position& velocity);
  void jump();

private:
  virtual void syncChildren() override;

private:
  Position mJumpAcceleration;
  Position mJumpVelocity;
  CircleShape mBall;
  FlappyCatMascot mMascot;
  modifier_type mResetModifier;
  update_modifier_type mUpdateModifier;
};


#endif //FLAPPY_CAT_FLAPPYCATHERO_H
