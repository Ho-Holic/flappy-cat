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
  Position wallSize() const;
  Position cameraSize() const;
  Position backgroundDisplacement() const;
  Position foregroundDisplacement() const;
  Position::value_type gravity() const;
  Position::value_type heroRadius() const;
  Position::value_type cloudRadius() const;
  Position::value_type plateWidth() const;

public:
  Position::value_type randomOffsetFrom(Position::value_type initial,
                                        Position::value_type maxOffset,
                                        Sign sign = Sign::Positive);

  Position::value_type clampedRandomOffsetFrom(Position::value_type initial,
                                               Position::value_type maxOffset,
                                               Sign sign = Sign::Positive);
private:
  std::random_device mRandomDevice;
  std::mt19937 mGenerator;
  FlappyCatColorScheme mColorScheme;
};


#endif //FLAPPY_CAT_FLAPPYCATSIZECONSTANTS_H
