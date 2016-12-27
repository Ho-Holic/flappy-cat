// self
#include "FlappyCatGameConstants.h"


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

float FlappyCatGameConstants::ballRadius() const {
  return 50.f;
}













