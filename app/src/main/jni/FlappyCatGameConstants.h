#ifndef FLAPPY_CAT_FLAPPYCATGAMECONSTANT_H
#define FLAPPY_CAT_FLAPPYCATGAMECONSTANT_H

// self
#include <core/Position.h>

class FlappyCatGameConstants {
public:
  Position houseSize() const;
  Position blockSize() const;
  Position gravity() const;

public:
  float ballRadius() const;
  Position::position_type plateWidth() const;
  Position::position_type gapInterval() const;
};


#endif //FLAPPY_CAT_FLAPPYCATSIZECONSTANTS_H
