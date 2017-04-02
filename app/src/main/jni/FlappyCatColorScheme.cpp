
// self
#include "FlappyCatColorScheme.h"

// engine
#include <core/HslColor.h>
#include <core/Log.h>

FlappyCatColorScheme::FlappyCatColorScheme()
: mRandomDevice()
, mGenerator(mRandomDevice())
, mScheme(ColorsSize, Color()) {

  generateNewScheme();
}

Color FlappyCatColorScheme::random() const {

  std::uniform_int_distribution<uint32_t> distribution; // from 0 to 2^32

  uint32_t fullColor = distribution(mGenerator);

  return Color(fullColor | 0xff); // set alpha channel to 255
}

void FlappyCatColorScheme::generateNewScheme() {

  std::uniform_real_distribution<HslColor::value_type> distribution(0, 360);
  HslColor::value_type hue = distribution(mGenerator);
  HslColor heroColor(hue, 100.0, 50.0);


  HslColor blockColor(heroColor);
  blockColor.setLuminance(25.0);

  HslColor dirtColor(blockColor);
  dirtColor.setSaturation(15.0);
  dirtColor.setLuminance(20.0);


  HslColor backgroundColor(heroColor);
  backgroundColor.rotateHue(180.0);
  backgroundColor.setSaturation(25.0);
  backgroundColor.setLuminance(90.0);

  HslColor cloudColor(backgroundColor);
  cloudColor.setSaturation(100.0);

  HslColor houseColor(heroColor);
  houseColor.rotateHue(180.0);
  houseColor.setSaturation(10.0);
  houseColor.setLuminance(55.0);


  mScheme[BackgroundColor] = backgroundColor.toRgb();
  mScheme[BlockColor]      = blockColor.toRgb();
  mScheme[HeroColor]       = heroColor.toRgb(128);
  mScheme[HouseColor]      = houseColor.toRgb();
  mScheme[CloudColor]      = cloudColor.toRgb();
  mScheme[DirtColor]       = dirtColor.toRgb();
}



Color FlappyCatColorScheme::background() const {

  return mScheme[BackgroundColor];
}

Color FlappyCatColorScheme::block() const {

  return mScheme[BlockColor];
}

Color FlappyCatColorScheme::hero() const {

  return mScheme[HeroColor];
}

Color FlappyCatColorScheme::house() const {
  return mScheme[HouseColor];
}

Color FlappyCatColorScheme::cloud() const {
  return mScheme[CloudColor];
}

Color FlappyCatColorScheme::dirt() const {
  return mScheme[DirtColor];
}
