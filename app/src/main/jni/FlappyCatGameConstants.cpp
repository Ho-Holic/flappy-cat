// self
#include "FlappyCatGameConstants.h"

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

Position FlappyCatGameConstants::blockSize() const {
  return Position(300, 200);
}

Position::position_type FlappyCatGameConstants::plateWidth() const {
  return 1000.f;
}

Position::position_type FlappyCatGameConstants::gapInterval() const {
  return 300.f;
}

Position FlappyCatGameConstants::gravity() const {
  return Position(0, -10.f);
}

float FlappyCatGameConstants::heroRadius() const {
  return 50.f;
}

Position::position_type
FlappyCatGameConstants::randomOffsetFrom(Position::position_type initial,
                                         Position::position_type maxOffset,
                                         Sign sign) {

  std::normal_distribution<float> distribution(initial, maxOffset);
  return sign == Sign::Positive ? std::abs(distribution(mGenerator))
                                : distribution(mGenerator);
}

float FlappyCatGameConstants::cloudRadius() const {
  return 20.f;
}

Position FlappyCatGameConstants::spikeSize() const {
  return Position(25.f, 25.f);
}
