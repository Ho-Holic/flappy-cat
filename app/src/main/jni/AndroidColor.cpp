// self
#include "AndroidColor.h"

// stl
#include <random>

AndroidColor::AndroidColor()
: mRed(0)
, mGreen(0)
, mBlue(0)
, mAlpha(255) {
  //
}

AndroidColor::AndroidColor(uint32_t rgbaColor)
: mRed  (static_cast<uint8_t>((rgbaColor & 0xFF000000) >> 24))
, mGreen(static_cast<uint8_t>((rgbaColor & 0x00FF0000) >> 16))
, mBlue (static_cast<uint8_t>((rgbaColor & 0x0000FF00) >> 8))
, mAlpha(static_cast<uint8_t>((rgbaColor & 0x000000FF) >> 0)) {
  //
}

uint8_t AndroidColor::r() const {
  return mRed;
}

uint8_t AndroidColor::g() const {
  return mGreen;
}

uint8_t AndroidColor::b() const {
  return mBlue;
}

uint8_t AndroidColor::alpha() const {
  return mAlpha;
}

AndroidColor AndroidColor::random() {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> dis; // from 0 to 2^32

  uint32_t fullColor = dis(gen);

  return AndroidColor(fullColor | 0xff); // set alpha channel to 255
}


