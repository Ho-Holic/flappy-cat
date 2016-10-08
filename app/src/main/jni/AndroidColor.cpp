// self
#include "AndroidColor.h"

// stl
#include <random>

AndroidColor::AndroidColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha)
: mRed(r)
, mGreen(g)
, mBlue(b)
, mAlpha(alpha) {
  //
}

AndroidColor::AndroidColor(uint8_t r, uint8_t g, uint8_t b)
: AndroidColor(r, g, b, 255) {
  //
}



AndroidColor::AndroidColor()
: AndroidColor(0, 0, 0, 255) {
  //
}

AndroidColor::AndroidColor(uint32_t rgbaColor)
: AndroidColor(
  static_cast<uint8_t>((rgbaColor & 0xFF000000) >> 24),
  static_cast<uint8_t>((rgbaColor & 0x00FF0000) >> 16),
  static_cast<uint8_t>((rgbaColor & 0x0000FF00) >> 8 ),
  static_cast<uint8_t>((rgbaColor & 0x000000FF) >> 0 )) {
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

AndroidColor AndroidColor::grayscale() const {

  // explicit integer promotion `int(mRed)`

  uint8_t mid = static_cast<uint8_t>((int(mRed) + mGreen + mBlue) / 3);
  return AndroidColor(mid, mid, mid, 255);
}

AndroidColor& AndroidColor::operator *= (float factor) {
  mRed   = static_cast<uint8_t>(mRed   * factor);
  mGreen = static_cast<uint8_t>(mGreen * factor);
  mBlue  = static_cast<uint8_t>(mBlue  * factor);
  // alpha does not change
  return *this;
}

// free functions


AndroidColor operator + (const AndroidColor& left, const AndroidColor& right)  {

  // explicit integer promotion `int(left.mRed)`

  return AndroidColor(uint8_t(std::min(int(left.mRed)   + right.mRed,   255)),
                      uint8_t(std::min(int(left.mGreen) + right.mGreen, 255)),
                      uint8_t(std::min(int(left.mBlue)  + right.mBlue,  255)),
                      uint8_t(std::min(int(left.mAlpha) + right.mAlpha, 255)));
}

AndroidColor operator - (const AndroidColor& left, const AndroidColor& right) {

  // explicit integer promotion `int(left.mRed)`

  return AndroidColor(uint8_t(std::max(int(left.mRed)   - right.mRed,   0)),
                      uint8_t(std::max(int(left.mGreen) - right.mGreen, 0)),
                      uint8_t(std::max(int(left.mBlue)  - right.mBlue,  0)),
                      uint8_t(std::max(int(left.mAlpha) - right.mAlpha, 0)));
}



AndroidColor operator * (const AndroidColor& left, const AndroidColor& right)  {

  // explicit integer promotion `int(left.mRed)`

  return AndroidColor(uint8_t(int(left.mRed)   * right.mRed   / 255),
                      uint8_t(int(left.mGreen) * right.mGreen / 255),
                      uint8_t(int(left.mBlue)  * right.mBlue  / 255),
                      uint8_t(int(left.mAlpha) * right.mAlpha / 255));
}

AndroidColor operator*(float factor, const AndroidColor& right) {

  return AndroidColor(right) *= factor;
}

AndroidColor operator*(const AndroidColor& left, float factor) {

  return AndroidColor(left) *= factor;
}










