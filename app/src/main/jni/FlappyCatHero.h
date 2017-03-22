#ifndef FLAPPY_CAT_FLAPPYCATHERO_H
#define FLAPPY_CAT_FLAPPYCATHERO_H

// engine
#include <prototype/CircleShape.h>

// self
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
  virtual const Position& position() const override;
  virtual void moveTo(const Position& position) override;
  virtual void reset() override;
  virtual void update(const FrameDuration& time);

public:
  void setColor(const Color& color);
  void setResetModifier(const modifier_type& modifier);
  void setUpdateModifier(const update_modifier_type& modifier);
  void setRadius(Position::value_type radius);
  Position::value_type radius() const;

private:
  CircleShape mBall;
  modifier_type mResetModifier;
  update_modifier_type mUpdateModifier;
};


#endif //FLAPPY_CAT_FLAPPYCATHERO_H
