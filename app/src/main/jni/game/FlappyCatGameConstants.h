#ifndef FLAPPY_CAT_FLAPPYCATGAMECONSTANT_H
#define FLAPPY_CAT_FLAPPYCATGAMECONSTANT_H

// game
#include "FlappyCatColorScheme.h"

// engine
#include <core/Position.h>

// stl
#include <random>

enum class Daytime {
  Day,
  Night
};

class FlappyCatGameConstants {
public:
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
  Position heroPosition() const;
  Position heroSize() const;
  Position cloudSize() const;

public:
  Position wallOffset() const;
  Position houseOffset() const;
  Position cloudOffset() const;
  Position skyOffset() const;

public:
  Position gravity() const;
  Position backgroundDisplacement() const;
  Position foregroundDisplacement() const;
  Position jumpAcceleration() const;
  Position jumpVelocity() const;

public:
  Position cloudParts() const;

public:
  Position::value_type randomOffsetFrom(Position::value_type initial,
                                        Position::value_type maxOffset);

  Position::value_type clampedRandomOffsetFrom(Position::value_type initial,
                                               Position::value_type maxOffset);
private:
  Daytime chooseDaytime();
private:
  std::random_device mRandomDevice;
  std::mt19937 mGenerator;
  FlappyCatColorScheme mColorScheme;
  std::vector<Position> mConstants;
  int32_t mDaytimeFactor;
};

enum FlappyCatGameConstants::Constants : size_t {

  CameraSize,

  BarricadePosition,
  BarricadeSize,
  WallSize,
  WallOffset,

  CityPosition,
  CitySize,
  HouseSize,
  HouseOffset,

  FloorPosition,
  FloorSize,

  HeroPosition,
  HeroSize,

  CloudSize,
  CloudOffset,
  SkyOffset,
  CloudParts,

  ConstantsSize
};



#endif //FLAPPY_CAT_FLAPPYCATSIZECONSTANTS_H
