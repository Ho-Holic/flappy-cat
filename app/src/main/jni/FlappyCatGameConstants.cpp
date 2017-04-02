// self
#include "FlappyCatGameConstants.h"
#include "style/BackportCpp17.h"

FlappyCatGameConstants::FlappyCatGameConstants()
: mRandomDevice()
, mGenerator(mRandomDevice())
, mColorScheme()
, mConstants(ConstantsSize, Position()) {

  reset();
}

void FlappyCatGameConstants::reset() {

  mColorScheme.generateNewScheme();

  Position::value_type mPlateWidth = plateWidth();

  mConstants[CameraSize]        = Position(1080.f, 1920.f);
  mConstants[WallSize]          = Position(180, 1725);
  mConstants[HouseSize]         = Position(100, 150);
  mConstants[FloorPosition]     = Position(-mPlateWidth, -800.f);
  mConstants[FloorSize]         = Position(mPlateWidth * 2.f, 200.f);
  mConstants[CityPosition]      = Position(-mPlateWidth, -800.f);
  mConstants[CitySize]          = Position(mPlateWidth * 2.f, 0.f);
  mConstants[BarricadePosition] = Position(-mPlateWidth, -775.f);
  mConstants[BarricadeSize]     = Position(mPlateWidth * 2.f, 0.f);

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

Position FlappyCatGameConstants::floorPosition() const {
  return mConstants[FloorPosition];
}

Position FlappyCatGameConstants::floorSize() const {
  return mConstants[FloorSize];
}

Position::value_type FlappyCatGameConstants::plateWidth() const {
  return 1000.f;
}

Position::value_type FlappyCatGameConstants::gravity() const {
  return 100.f;
}

Position::value_type FlappyCatGameConstants::heroRadius() const {
  return 50.f;
}

Position::value_type FlappyCatGameConstants::cloudRadius() const {
  return 20.f;
}




Position FlappyCatGameConstants::backgroundDisplacement() const {
  return Position(-5.f, 0.f);
}

Position FlappyCatGameConstants::foregroundDisplacement() const {
  return Position(-10.f, 0.f);
}

Position::value_type
FlappyCatGameConstants::randomOffsetFrom(Position::value_type initial,
                                         Position::value_type maxOffset,
                                         Sign sign) {

  std::normal_distribution<Position::value_type> distribution(initial, maxOffset);

  auto number = distribution(mGenerator);

  return sign == Sign::Positive ? std::abs(number)
                                : number;

}

Position::value_type
FlappyCatGameConstants::clampedRandomOffsetFrom(Position::value_type initial,
                                         Position::value_type maxOffset,
                                         Sign sign) {

  std::normal_distribution<Position::value_type> distribution(initial, maxOffset);

  auto number = distribution(mGenerator);

  return sign == Sign::Positive ? std::abs(backport::std::clamp(number,
                                                                initial - maxOffset,
                                                                initial + maxOffset))
                                : backport::std::clamp(number,
                                                       initial - maxOffset,
                                                       initial + maxOffset);
}


