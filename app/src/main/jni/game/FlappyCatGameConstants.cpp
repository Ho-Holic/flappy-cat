// game
#include "FlappyCatGameConstants.h"

// style
#include <style/BackportCpp17.h>

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

  Position::value_type plateWidth = 1000.f; // TODO: remove tmp variable

  Position::value_type offscreenMargin = 1.f; // one column beyond front and back part of a screen

  Position::value_type halfCameraX = cameraSize.x() / 2.f;
  Position::value_type halfCameraY = cameraSize.y() / 2.f;
  Position::value_type offsetFloorY = halfCameraY * 0.8f; // ground takes 20%

//  Position::value_type vanishWallX = 0.f;
//  Position::value_type vanishCityX = 0.f;
//  Position::value_type vanishFloorX = 0.f;


  // camera
  mConstants[CameraSize]        = cameraSize;

  // floor
  mConstants[FloorPosition]     = Position(-plateWidth, -offsetFloorY);
  mConstants[FloorSize]         = Position(plateWidth * 2.f, halfCameraY - offsetFloorY);
  mConstants[FloorOrganicSurfaceSize] = Position(0.f, 20.f);
  mConstants[FloorSpikesSize]   = Position(25.f, 25.f);

  // barricade
  mConstants[WallSize]          = Position(180.f, halfCameraY + offsetFloorY);
  mConstants[BetweenWallOffset] = 2.2f * Position(180.f, 0.f);
  mConstants[BarricadePosition] = Position(-plateWidth, -offsetFloorY);
  mConstants[BarricadeSize]     = Position(plateWidth * 2.f, halfCameraY + offsetFloorY);
  mConstants[WallOffset]        = Position(0.f, 300.f);

  // city
  mConstants[HouseOffset]       = Position(0.f, 200.f);
  mConstants[HouseSize]         = Position(100.f, 150.f);
  mConstants[CityPosition]      = Position(-plateWidth, -offsetFloorY);
  mConstants[CitySize]          = Position(plateWidth * 2.f, 0.f);

  // hero
  mConstants[HeroPosition]      = Position(-300.f, 0.f);
  mConstants[HeroSize]          = Position(50.f, 50.f);

  // clouds
  // Daytime::Day constants
  mConstants[CloudSize]         = Position(20.f, 20.f);
  mConstants[CloudOffset]       = Position(0.f, 100.f);
  mConstants[SkyOffset]         = Position(0.f, 500.f);
  mConstants[CloudParts]        = Position(100.f, 0.f);

  if (daytime == Daytime::Night) {
    mConstants[CloudSize]         = Position(1.f, 0.f);
    mConstants[CloudOffset]       = Position(0.f, 5.f);
    mConstants[SkyOffset]         = Position(0.f, 500.f);
    mConstants[CloudParts]        = Position(50.f, 0.f);
  }

}

const FlappyCatColorScheme& FlappyCatGameConstants::colorScheme() const {

  return mColorScheme;
}

Position FlappyCatGameConstants::cameraSize() const {

  return mConstants[CameraSize] ;
}

Position FlappyCatGameConstants::cityPosition() const {
  return mConstants[CityPosition];
}

Position FlappyCatGameConstants::citySize() const {
  return mConstants[CitySize];
}

Position FlappyCatGameConstants::houseSize() const {
  return mConstants[HouseSize];
}

Position FlappyCatGameConstants::barricadePosition() const {
  return mConstants[BarricadePosition];
}

Position FlappyCatGameConstants::barricadeSize() const {
  return mConstants[BarricadeSize];
}

Position FlappyCatGameConstants::wallSize() const {
  return mConstants[WallSize];
}

Position FlappyCatGameConstants::betweenWallOffset() const {
  return mConstants[BetweenWallOffset];
}

Position FlappyCatGameConstants::floorPosition() const {
  return mConstants[FloorPosition];
}

Position FlappyCatGameConstants::floorSize() const {
  return mConstants[FloorSize];
}

Position FlappyCatGameConstants::organicSurfaceSize() const {
  return mConstants[FloorOrganicSurfaceSize];
}

Position FlappyCatGameConstants::spikesSize() const {
  return mConstants[FloorSpikesSize];
}

Position FlappyCatGameConstants::heroPosition() const {
  return mConstants[HeroPosition];
}

Position FlappyCatGameConstants::heroSize() const {
  return mConstants[HeroSize];
}

Position FlappyCatGameConstants::wallOffset() const {
  return mConstants[WallOffset];
}

Position FlappyCatGameConstants::houseOffset() const {
  return mConstants[HouseOffset];
}

Position FlappyCatGameConstants::cloudSize() const {
  return mConstants[CloudSize];
}

Position FlappyCatGameConstants::cloudOffset() const {
  return mConstants[CloudOffset];
}

Position FlappyCatGameConstants::skyOffset() const {
  return mConstants[SkyOffset];
}

Position FlappyCatGameConstants::cloudParts() const {
  return mConstants[CloudParts];
}

Position FlappyCatGameConstants::jumpAcceleration() const {
  return Position(0.f, -800.f);
}

Position FlappyCatGameConstants::jumpVelocity() const {
  return Position(0.f, 800.f);
}

Position FlappyCatGameConstants::gravity() const {
  return Position(0.f, 100.f);
}

Position FlappyCatGameConstants::backgroundDisplacement() const {
  return Position(-5.f, 0.f);
}

Position FlappyCatGameConstants::foregroundDisplacement() const {
  return Position(-8.f, 0.f);
}

Position::value_type
FlappyCatGameConstants::randomOffsetFrom(Position::value_type initial,
                                         Position::value_type maxOffset) {

  std::normal_distribution<Position::value_type> distribution(initial, maxOffset);

  return distribution(mGenerator);
}

Position::value_type
FlappyCatGameConstants::clampedRandomOffsetFrom(Position::value_type initial,
                                                Position::value_type maxOffset) {

  return backport::std::clamp(randomOffsetFrom(initial, maxOffset),
                              initial - maxOffset,
                              initial + maxOffset);
}
