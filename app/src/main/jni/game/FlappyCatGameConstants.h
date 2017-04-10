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

  // If you have error 'Error: 'FlappyCatColorScheme' does not name a type'
  // Then Android Studio accidentally insert following line
  //
  //     #include "FlappyCatGameConstants.h"
  //
  // to 'FlappyCatColorScheme.h'. Android studio really wants this line there
  // and don't want to deal with forward declarations of modern enums =)
  const FlappyCatColorScheme& colorScheme() const;

  Position operator[](Constants index) const;

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
  BarricadeWallSize,
  BarricadeBetweenWallOffset,
  BarricadeWallGapDisplacement,

  CityPosition,
  CitySize,
  CityHouseSize,
  CityHouseOffset,

  FloorPosition,
  FloorSize,
  FloorOrganicSurfaceSize,
  FloorSpikesSize,

  HeroPosition,
  HeroSize,

  SkyCloudSize,
  SkyCloudOffset,
  SkyOffset,
  SkyCloudParts,

  PhysicsGravity,
  PhysicsBackgroundDisplacement,
  PhysicsForegroundDisplacement,
  PhysicsJumpAcceleration,
  PhysicsJumpVelocity,

  ConstantsSize
};

#endif //FLAPPY_CAT_FLAPPYCATSIZECONSTANTS_H
