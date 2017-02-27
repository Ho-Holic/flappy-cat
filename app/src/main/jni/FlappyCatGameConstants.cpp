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
  return Position(300, 1725);
}

Position::value_type FlappyCatGameConstants::plateWidth() const {
  return 1000.f;
}

Position::value_type FlappyCatGameConstants::gapInterval() const {
  return 600.f;
}

Position::value_type FlappyCatGameConstants::gravity() const {
  return 40.f;
}

float FlappyCatGameConstants::heroRadius() const {
  return 50.f;
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

float FlappyCatGameConstants::cloudRadius() const {
  return 20.f;
}

Position FlappyCatGameConstants::spikeSize() const {
  return Position(25.f, 25.f);
}
