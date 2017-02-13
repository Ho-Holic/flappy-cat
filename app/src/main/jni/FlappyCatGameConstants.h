#ifndef FLAPPY_CAT_FLAPPYCATGAMECONSTANT_H
#define FLAPPY_CAT_FLAPPYCATGAMECONSTANT_H

// self
#include "FlappyCatColorScheme.h"

// engine
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
  void reset();
  const FlappyCatColorScheme& colorScheme() const;

public:
  Position houseSize() const;
  Position blockSize() const;
  Position spikeSize() const;
  Position::position_type gravity() const;

public:
  float heroRadius() const;
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
  FlappyCatColorScheme mColorScheme;
};


#endif //FLAPPY_CAT_FLAPPYCATSIZECONSTANTS_H
