
// self
#include "FlappyCatColorScheme.h"

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







