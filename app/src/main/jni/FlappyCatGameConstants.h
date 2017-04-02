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
  enum class Sign { Positive, Both };
  enum Constants : size_t;

public:
  FlappyCatGameConstants();

public:
  void reset();
  const FlappyCatColorScheme& colorScheme() const;

public:
  Position cameraSize() const;
  Position barricadePosition() const;
  Position barricadeSize() const;
  Position wallSize() const;
  Position floorPosition() const;
  Position floorSize() const;
  Position cityPosition() const;
  Position citySize() const;
  Position houseSize() const;

  Position backgroundDisplacement() const;
  Position foregroundDisplacement() const;

  Position::value_type gravity() const;
  Position::value_type heroRadius() const;
  Position::value_type cloudRadius() const;
  Position::value_type plateWidth() const;

public:
  // TODO: remove 'Sign sign' just call abs directly in the code
  Position::value_type randomOffsetFrom(Position::value_type initial,
                                        Position::value_type maxOffset,
                                        Sign sign = Sign::Positive);

  // TODO: remove 'Sign sign' just call abs directly in the code
  Position::value_type clampedRandomOffsetFrom(Position::value_type initial,
                                               Position::value_type maxOffset,
                                               Sign sign = Sign::Positive);
private:
  std::random_device mRandomDevice;
  std::mt19937 mGenerator;
  FlappyCatColorScheme mColorScheme;
  std::vector<Position> mConstants;
};

enum FlappyCatGameConstants::Constants : size_t {

  CameraSize,

  BarricadePosition,
  BarricadeSize,
  WallSize,

  CityPosition,
  CitySize,
  HouseSize,

  FloorPosition,
  FloorSize,

  ConstantsSize
};

#endif //FLAPPY_CAT_FLAPPYCATSIZECONSTANTS_H
