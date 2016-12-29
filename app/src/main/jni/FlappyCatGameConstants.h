#ifndef FLAPPY_CAT_FLAPPYCATGAMECONSTANT_H
#define FLAPPY_CAT_FLAPPYCATGAMECONSTANT_H

// self
#include <core/Position.h>

// stl
#include <random>

class FlappyCatGameConstants {
public:
  enum class Sign {
    Positive,
    Both
  };
public:
  FlappyCatGameConstants();

public:
  Position houseSize() const;
  Position blockSize() const;
  Position gravity() const;

public:
  float ballRadius() const;
  float cloudRadius() const;
  Position::position_type plateWidth() const;
  Position::position_type gapInterval() const;

public:
  Position::position_type randomOffsetFrom(Position::position_type initial,
                                           Position::position_type maxOffset,
                                           Sign sign = Sign::Positive);

private:
  std::random_device mRandomDevice;
  std::mt19937 mGenerator;
};


#endif //FLAPPY_CAT_FLAPPYCATSIZECONSTANTS_H
