
// self
#include "FlappyCatColorScheme.h"

// stl
#include <random>

FlappyCatColorScheme::FlappyCatColorScheme()
: mScheme() {
  mScheme.reserve(ColorsSize);
  generateNewScheme();
}

void FlappyCatColorScheme::generateNewScheme() {

  mScheme[Background] = Color(255, 255, 255);
  mScheme[Block]      = Color(128, 0, 0);
  mScheme[Ball]       = Color(255, 0, 0);
}

Color FlappyCatColorScheme::background() const {

  return mScheme[Background];
}

Color FlappyCatColorScheme::block() const {

  return mScheme[Block];
}

Color FlappyCatColorScheme::ball() const {

  return mScheme[Ball];
}

Color FlappyCatColorScheme::random() {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> dis; // from 0 to 2^32

  uint32_t fullColor = dis(gen);

  return Color(fullColor | 0xff); // set alpha channel to 255
}
