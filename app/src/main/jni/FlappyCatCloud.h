#ifndef FLAPPY_CAT_FLAPPYCATCLOUD_H
#define FLAPPY_CAT_FLAPPYCATCLOUD_H

// engine
#include <prototype/CircleShape.h>

// self
#include "FlappyCatEntity.h"

// stl
#include <vector>


class FlappyCatCloud : public FlappyCatEntity {
public:
  using entity_type = CircleShape;
  using modifier_type = std::function<void(entity_type&)>;

public:
  FlappyCatCloud();

public:
  void initialize();
  void setResetModifier(const modifier_type& modifier);

public:
  virtual void drawOn(const Window& window) const override;
  virtual const Position& position() const override;
  virtual void moveTo(const Position& position) override;
  virtual void setColor(const Color& color) override;
  virtual void reset() override;

public:
  std::vector<entity_type> mCloudParts;
  modifier_type mResetModifier;
};


#endif //FLAPPY_CAT_FLAPPYCATCLOUD_H
