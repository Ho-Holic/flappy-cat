#ifndef FLAPPY_CAT_TRANSFORMATION_H
#define FLAPPY_CAT_TRANSFORMATION_H

// self
#include "Position.h"

class Transformation {
public:
  virtual ~Transformation() = default;

public:
  virtual void setOrigin(const Position& position) = 0;
  virtual const Position& origin() const = 0;
  virtual void setPosition(const Position& position) = 0;
  virtual const Position& getPosition() const = 0;
};


#endif //FLAPPY_CAT_TRANSFORMATION_H
