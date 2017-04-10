
// game
#include "FlappyCatColorScheme.h"
#include "FlappyCatGameConstants.h"

// engine
#include <core/HslColor.h>
#include <core/Log.h>

// style
#include <style/Guidelines.h>

FlappyCatColorScheme::FlappyCatColorScheme()
: mRandomDevice()
, mGenerator(mRandomDevice())
, mScheme(ColorsSize, Color()) {
  //
}

Color FlappyCatColorScheme::random() const {

  std::uniform_int_distribution<uint32_t> distribution; // from 0 to 2^32

  uint32_t fullColor = distribution(mGenerator);

  return Color(fullColor | 0xff); // set alpha channel to 255
}

Color FlappyCatColorScheme::operator[](FlappyCatColorScheme::Colors index) const {

  REQUIRE(TAG, index < ColorsSize, "mScheme is out of bounds");
  return mScheme[index];
}

void FlappyCatColorScheme::generateNewScheme(Daytime daytime) {

  switch (daytime) {
    case Daytime::Day:   generateDayScheme(); break;
    case Daytime::Night: generateNightScheme(); break;
  }
}

void FlappyCatColorScheme::generateNightScheme() {

  std::uniform_real_distribution<HslColor::value_type> distribution(0.0, 360.0);
  HslColor::value_type hue = distribution(mGenerator);

  HslColor heroColor(hue, 100.0, 50.0);

  HslColor backgroundColor(heroColor);
  backgroundColor.setLuminance(5.0);

  HslColor blockColor(backgroundColor);
  blockColor.rotateHue(240.0);
  blockColor.setSaturation(40.0);
  blockColor.setLuminance(25.0);

  HslColor houseColor(backgroundColor);
  houseColor.rotateHue(120.0);
  houseColor.setSaturation(100.0);
  houseColor.setLuminance(60.0);

  HslColor dirtColor(backgroundColor);

  HslColor cloudColor(backgroundColor);
  cloudColor.setLuminance(100.0);


  mScheme[BackgroundColor] = backgroundColor.toRgb();
  mScheme[BlockColor]      = blockColor.toRgb();
  mScheme[HeroColor]       = heroColor.toRgb(128);
  mScheme[HouseColor]      = houseColor.toRgb();
  mScheme[CloudColor]      = cloudColor.toRgb();
  mScheme[DirtColor]       = dirtColor.toRgb();
  mScheme[MascotBodyColor] = Color(0, 0, 0);
  mScheme[MascotScarfColor] = Color(255, 255, 255);
  mScheme[MascotMouthColor] = Color(255, 128, 0);

}

void FlappyCatColorScheme::generateDayScheme() {

  std::uniform_real_distribution<HslColor::value_type> distribution(0.0, 360.0);
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
  mScheme[MascotBodyColor] = Color(0, 0, 0);
  mScheme[MascotScarfColor] = Color(255, 255, 255);
  mScheme[MascotMouthColor] = Color(255, 128, 0);
}
