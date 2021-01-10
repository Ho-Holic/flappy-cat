#ifndef FLAPPY_CAT_FLAPPYCATCLOUD_H
#define FLAPPY_CAT_FLAPPYCATCLOUD_H

// engine
#include <prototype/CircleShape.hpp>

// game
#include "FlappyCatEntity.hpp"

// stl
#include <vector>


class FlappyCatCloud : public FlappyCatEntity {
public:
  using entity_type = CircleShape;
  using modifier_type = std::function<void(entity_type&)>;

public:
  FlappyCatCloud(const FlappyCatGameConstants& gameConstants);

public:
  virtual void initialize() override;
  virtual void drawOn(const Window& window) const override;
  virtual void reset() override;

public:
  void setResetModifier(const modifier_type& modifier);
  void setColor(const Color& color);
  void setParts(float parts);
public:
  float mParts;
  std::vector<entity_type> mCloudParts;
  modifier_type mResetModifier;
};


#endif //FLAPPY_CAT_FLAPPYCATCLOUD_H
