// self
#include "FlappyCatGameConstants.h"
#include "style/BackportCpp17.h"

FlappyCatGameConstants::FlappyCatGameConstants()
: mRandomDevice()
, mGenerator(mRandomDevice())
, mColorScheme() {

  reset();
}

void FlappyCatGameConstants::reset() {

  mColorScheme.generateNewScheme();
}

const FlappyCatColorScheme& FlappyCatGameConstants::colorScheme() const {

  return mColorScheme;
}

Position FlappyCatGameConstants::houseSize() const {
  return Position(100, 150);
}

Position FlappyCatGameConstants::wallSize() const {
  return Position(180, 1725);
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
                                                                initial,
                                                                initial + maxOffset))
                                : backport::std::clamp(number,
                                                       initial - maxOffset,
                                                       initial + maxOffset);
}

Position FlappyCatGameConstants::cameraSize() const {

  return Position(1080.f, 1920.f);
}

Position FlappyCatGameConstants::backgroundDisplacement() const {
  return Position(-5.f, 0.f);
}

Position FlappyCatGameConstants::foregroundDisplacement() const {
  return Position(-10.f, 0.f);
}
