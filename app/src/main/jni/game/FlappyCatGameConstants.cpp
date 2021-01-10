// game
#include "FlappyCatGameConstants.hpp"

// engine
#include <style/Guidelines.hpp>
#include <core/Log.hpp>

FlappyCatGameConstants::FlappyCatGameConstants()
: mRandomDevice()
, mGenerator(mRandomDevice())
, mColorScheme()
, mConstants(ConstantsSize, Position())
, mDaytimeFactor(0) {

  /**
   * TODO: Remove 'reset()' and 'mDaytimeFactor = 0'
   *
   * Call is not needed but directly we can't remove it
   * This would cause all objects to disappear
   * because 'initialize()' function uses 'mConstants'
   * Seems this is deep arch issue, figure out how to
   * improve the design
   */
  reset();
  mDaytimeFactor = 0;
}

Daytime FlappyCatGameConstants::chooseDaytime() {

  // small code for day/night cycling

  enum {
    Period = 3
  };

  Daytime daytime = (mDaytimeFactor < Period) ? Daytime::Day
                                              : Daytime::Night;

  mDaytimeFactor = (mDaytimeFactor + 1) % (Period * 2);

  return daytime;
}


Position FlappyCatGameConstants::operator[](FlappyCatGameConstants::Constants index) const {

  REQUIRE(TAG, index < ConstantsSize, "mConstants out of bounds");
  return mConstants[index];
}

void FlappyCatGameConstants::reset() {

  Daytime daytime = chooseDaytime();

  mColorScheme.generateNewScheme(daytime);

  Position cameraSize = Position(1080.f, 1920.f);

  float plateWidth = 1000.f;

  float halfCameraY = cameraSize.y() / 2.f;
  float offsetFloorY = halfCameraY * 0.8f; // ground takes 20%


  // camera
  mConstants[CameraSize] = cameraSize;

  // floor
  mConstants[FloorPosition]           = Position(-plateWidth, -offsetFloorY);
  mConstants[FloorSize]               = Position(plateWidth * 2.f, halfCameraY - offsetFloorY);
  mConstants[FloorOrganicSurfaceSize] = Position(0.f, 20.f);
  mConstants[FloorSpikesSize]         = Position(25.f, 25.f);

  // barricade
  mConstants[BarricadeWallSize]            = Position(180.f, halfCameraY + offsetFloorY);
  mConstants[BarricadeBetweenWallOffset]   = 2.2f * Position(180.f, 0.f);
  mConstants[BarricadePosition]            = Position(-plateWidth, -offsetFloorY);
  mConstants[BarricadeSize]                = Position(plateWidth * 2.f, halfCameraY + offsetFloorY);
  mConstants[BarricadeWallGapDisplacement] = Position(0.f, 300.f);
  mConstants[BarricadeStartOffset]         = Position(plateWidth * 2.5f, 0.f);

  // city
  mConstants[CityHouseOffset]   = Position(0.f, 200.f);
  mConstants[CityHouseSize]     = Position(100.f, 150.f);
  mConstants[CityPosition]      = Position(-plateWidth, -offsetFloorY);
  mConstants[CitySize]          = Position(plateWidth * 2.f, 0.f);

  // hero
  mConstants[HeroPosition]      = Position(-300.f, 0.f);
  mConstants[HeroSize]          = Position(50.f, 50.f);

  // clouds
  // constants for 'daytime == Daytime::Day'
  mConstants[SkyCloudSize]         = Position(20.f, 20.f);
  mConstants[SkyCloudOffset]       = Position(0.f, 100.f);
  mConstants[SkyOffset]            = Position(0.f, 500.f);
  mConstants[SkyCloudParts]        = Position(100.f, 0.f);

  if (daytime == Daytime::Night) {
    mConstants[SkyCloudSize]         = Position(1.f, 0.f);
    mConstants[SkyCloudOffset]       = Position(0.f, 5.f);
    mConstants[SkyOffset]            = Position(0.f, 500.f);
    mConstants[SkyCloudParts]        = Position(50.f, 0.f);
  }

  // physics
  mConstants[PhysicsGravity]                = Position(0.f, 100.f);
  mConstants[PhysicsBackgroundDisplacement] = Position(-2.8f, 0.f);
  mConstants[PhysicsForegroundDisplacement] = Position(-7.f, 0.f);
  mConstants[PhysicsJumpAcceleration]       = Position(0.f, -800.f);
  mConstants[PhysicsJumpVelocity]           = Position(0.f, 800.f);
}

const FlappyCatColorScheme& FlappyCatGameConstants::colorScheme() const {

  return mColorScheme;
}

float
FlappyCatGameConstants::randomOffsetFrom(float initial,
                                         float maxOffset) {

  std::normal_distribution<float> distribution(initial, maxOffset);

  return distribution(mGenerator);
}

float
FlappyCatGameConstants::clampedRandomOffsetFrom(float initial,
                                                float maxOffset) {

  return std::clamp(randomOffsetFrom(initial, maxOffset),
                              initial - maxOffset,
                              initial + maxOffset);
}
