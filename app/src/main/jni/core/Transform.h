#ifndef FLAPPY_CAT_TRANSFORM_H
#define FLAPPY_CAT_TRANSFORM_H

// self
#include "Position.h"

class Transform {
public:
  virtual ~Transform() = default;

public:
  virtual void setPosition(const Position& position) = 0;
  virtual const Position& getPosition() const = 0;
};


#endif //FLAPPY_CAT_TRANSFORM_H
