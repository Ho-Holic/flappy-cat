
// self
#include "FlappyCatColorScheme.h"


FlappyCatColorScheme::FlappyCatColorScheme()
: mRandomDevice()
, mGenerator(mRandomDevice())
, mScheme() {
  mScheme.reserve(ColorsSize);
  generateNewScheme();
}

void FlappyCatColorScheme::generateNewScheme() {

  mScheme[Background] = Color(255, 255, 255);
  mScheme[Block]      = Color(128, 0, 0);
  mScheme[Ball]       = Color(255, 0, 0);
  mScheme[House]      = Color(128, 128, 128);
  mScheme[Cloud]      = Color(225, 225, 225);
}

Color FlappyCatColorScheme::random() {

  std::uniform_int_distribution<uint32_t> distribution; // from 0 to 2^32

  uint32_t fullColor = distribution(mGenerator);

  return Color(fullColor | 0xff); // set alpha channel to 255
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

Color FlappyCatColorScheme::house() const {
  return mScheme[House];
}

Color FlappyCatColorScheme::cloud() const {
  return mScheme[Cloud];
}








