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
  Position::value_type gravity() const;

public:
  float heroRadius() const;
  float cloudRadius() const;
  Position::value_type plateWidth() const;
  Position::value_type gapInterval() const;

public:
  Position::value_type randomOffsetFrom(Position::value_type initial,
                                        Position::value_type maxOffset,
                                        Sign sign = Sign::Positive);

private:
  std::random_device mRandomDevice;
  std::mt19937 mGenerator;
  FlappyCatColorScheme mColorScheme;
};


#endif //FLAPPY_CAT_FLAPPYCATSIZECONSTANTS_H
