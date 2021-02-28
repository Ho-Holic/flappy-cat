
// game
#include "FlappyCatColorScheme.hpp"
#include "FlappyCatGameConstants.hpp"

// engine
#include <core/HslColor.hpp>
#include <core/Log.hpp>

// style
#include <style/Guidelines.hpp>

FlappyCatColorScheme::FlappyCatColorScheme()
    : m_randomDevice()
    , m_generator(m_randomDevice())
    , m_scheme(ColorsSize, Color())
{
    //
}

Color FlappyCatColorScheme::random() const
{

    std::uniform_int_distribution<uint32_t> distribution; // from 0 to 2^32

    uint32_t fullColor = distribution(m_generator);

    return Color(fullColor | 0xff); // set alpha channel to 255
}

Color FlappyCatColorScheme::operator[](FlappyCatColorScheme::Colors index) const
{

    REQUIRE(TAG, index < ColorsSize, "m_scheme is out of bounds");
    return m_scheme[index];
}

void FlappyCatColorScheme::generateNewScheme(Daytime daytime)
{

    switch (daytime) {
    case Daytime::Day:
        generateDayScheme();
        break;
    case Daytime::Night:
        generateNightScheme();
        break;
    }
}

void FlappyCatColorScheme::generateNightScheme()
{

    std::uniform_real_distribution<HslColor::value_type> distribution(0.0, 360.0);
    HslColor::value_type hue = distribution(m_generator);

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

    m_scheme[BackgroundColor] = backgroundColor.toRgb();
    m_scheme[BlockColor] = blockColor.toRgb();
    m_scheme[HeroColor] = heroColor.toRgb(128);
    m_scheme[HouseColor] = houseColor.toRgb();
    m_scheme[CloudColor] = cloudColor.toRgb();
    m_scheme[DirtColor] = dirtColor.toRgb();
    m_scheme[MascotBodyColor] = Color(0, 0, 0);
    m_scheme[MascotScarfColor] = Color(255, 255, 255);
    m_scheme[MascotMouthColor] = Color(255, 128, 0);
    m_scheme[TextColor] = Color(255, 255, 255);
}

void FlappyCatColorScheme::generateDayScheme()
{

    std::uniform_real_distribution<HslColor::value_type> distribution(0.0, 360.0);
    HslColor::value_type hue = distribution(m_generator);

    HslColor heroColor(hue, 100.0, 50.0);

    HslColor blockColor(heroColor);
    blockColor.rotateHue(150.0);
    blockColor.setSaturation(70.0);
    blockColor.setLuminance(40.0);

    HslColor dirtColor(blockColor);
    dirtColor.setLuminance(20.0);

    HslColor backgroundColor(heroColor);
    backgroundColor.rotateHue(210.0);
    backgroundColor.setSaturation(100.0);
    backgroundColor.setLuminance(85.0);

    HslColor cloudColor(heroColor);
    cloudColor.setLuminance(100.0);

    HslColor houseColor(heroColor);
    houseColor.rotateHue(210.0);
    houseColor.setSaturation(50.0);
    houseColor.setLuminance(55.0);

    m_scheme[BackgroundColor] = backgroundColor.toRgb();
    m_scheme[BlockColor] = blockColor.toRgb();
    m_scheme[HeroColor] = heroColor.toRgb(128);
    m_scheme[HouseColor] = houseColor.toRgb();
    m_scheme[CloudColor] = cloudColor.toRgb();
    m_scheme[DirtColor] = dirtColor.toRgb();
    m_scheme[MascotBodyColor] = Color(0, 0, 0);
    m_scheme[MascotScarfColor] = Color(255, 255, 255);
    m_scheme[MascotMouthColor] = Color(255, 128, 0);
    m_scheme[TextColor] = Color(0, 0, 0);
}
