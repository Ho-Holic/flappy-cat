// self
#include "HslColor.h"

// stl
#include <cmath>
#include <core/Log.h>
#include <style/Guidelines.h>

HslColor::HslColor(value_type hue, value_type saturation, value_type luminance)
  : mHue(hue)
  , mSaturation(saturation/100.0)
  , mLuminance(luminance/100.0) {
  //
}

Color HslColor::toRgb() {

  return toRgb(255);
}

Color HslColor::toRgb(uint8_t alpha) {

  value_type temporary_1
    = (mLuminance < 0.5) ? mLuminance * (1.0 + mSaturation)
                         : mLuminance + mSaturation - mLuminance * mSaturation;

  value_type temporary_2 = 2.0 * mLuminance - temporary_1;

  value_type hue = mHue / 360.0;

  value_type temporary_r = hue + 0.333;
  value_type temporary_g = hue;
  value_type temporary_b = hue - 0.333;

  if (temporary_r < 0.0) temporary_r += 1;
  if (temporary_r > 1.0) temporary_r -= 1;

  if (temporary_g < 0.0) temporary_g += 1;
  if (temporary_g > 1.0) temporary_g -= 1;

  if (temporary_b < 0.0) temporary_b += 1;
  if (temporary_b > 1.0) temporary_b -= 1;


  auto formula = [&](value_type temporary_channel) -> value_type {

    if ((6.0 * temporary_channel) < 1.0) {
      return temporary_2 + (temporary_1 - temporary_2) * 6.0 * temporary_channel;
    }
    else if ((2.0 * temporary_channel) < 1.0) {
      return temporary_1;
    }
    else if ((3.0 * temporary_channel) < 2.0) {
      return temporary_2 + (temporary_1 - temporary_2) * (0.666 - temporary_channel) * 6.0;
    }

    return temporary_2;
  };


  value_type red   = formula(temporary_r) * 255.0;
  value_type green = formula(temporary_g) * 255.0;
  value_type blue  = formula(temporary_b) * 255.0;

  return Color(static_cast<uint8_t>(red),
               static_cast<uint8_t>(green),
               static_cast<uint8_t>(blue),
               alpha);
}

HslColor::value_type HslColor::hue() const {
  return mHue;
}

HslColor::value_type HslColor::saturation() const {
  return mSaturation * 100.0;
}

HslColor::value_type HslColor::luminance() const {
  return mLuminance * 100.0;
}

void HslColor::setHue(value_type hue) {

  //REQUIRE(TAG, saturation >= 0.0 && saturation <= 360.0, "hue out of bounds");

  mHue = hue;
}

void HslColor::setSaturation(value_type saturation) {

  //REQUIRE(TAG, saturation >= 0.0 && saturation <= 100.0, "saturation out of bounds");

  mSaturation = saturation / 100.0;
}

void HslColor::setLuminance(value_type luminance) {

  //REQUIRE(TAG, luminance >= 0.0 && luminance <= 100.0, "luminance out of bounds");

  mLuminance = luminance / 100.0;
}

void HslColor::rotateHue(value_type shift) {

  //REQUIRE(TAG, shift >= 0.0, "only positive shift for now");

  mHue += shift;

  while (mHue > 360.0) {

    mHue -= 360.0;
  }

}

void HslColor::addSaturation(value_type shift) {

  mSaturation += (shift / 100.0);

  if (mSaturation > 1.0) mSaturation = 1.0;
  if (mSaturation < 0.0) mSaturation = 0.0;
}

void HslColor::addLuminance(value_type shift) {

  mLuminance += (shift / 100.0);
  if (mLuminance > 1.0) mLuminance = 1.0;
  if (mLuminance < 0.0) mLuminance = 0.0;
}