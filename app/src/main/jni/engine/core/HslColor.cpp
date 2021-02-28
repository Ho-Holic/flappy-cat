// engine
#include "HslColor.hpp"

// stl
#include <cmath>
#include <core/Log.hpp>

// style
#include <style/Guidelines.hpp>

HslColor::HslColor(value_type hue, value_type saturation, value_type luminance)
    : m_hue(hue)
    , m_saturation(saturation)
    , m_luminance(luminance)
{
    //
}

Color HslColor::toRgb()
{

    return toRgb(255);
}

Color HslColor::toRgb(uint8_t alpha)
{

    // normalization
    value_type hue = m_hue / 360.0;
    value_type luminance = m_luminance / 100.0;
    value_type saturation = m_saturation / 100.0;

    // algorithm
    value_type temporary_1
        = (luminance < 0.5) ? luminance * (1.0 + saturation)
                            : luminance + saturation - luminance * saturation;

    value_type temporary_2 = 2.0 * luminance - temporary_1;

    value_type temporary_r = hue + 0.333;
    value_type temporary_g = hue;
    value_type temporary_b = hue - 0.333;

    if (temporary_r < 0.0)
        temporary_r += 1;
    if (temporary_r > 1.0)
        temporary_r -= 1;

    if (temporary_g < 0.0)
        temporary_g += 1;
    if (temporary_g > 1.0)
        temporary_g -= 1;

    if (temporary_b < 0.0)
        temporary_b += 1;
    if (temporary_b > 1.0)
        temporary_b -= 1;

    auto formula = [&](value_type temporary_channel) -> value_type {
        if ((6.0 * temporary_channel) < 1.0) {
            return temporary_2 + (temporary_1 - temporary_2) * 6.0 * temporary_channel;
        } else if ((2.0 * temporary_channel) < 1.0) {
            return temporary_1;
        } else if ((3.0 * temporary_channel) < 2.0) {
            return temporary_2 + (temporary_1 - temporary_2) * (0.666 - temporary_channel) * 6.0;
        }

        return temporary_2;
    };

    value_type red = formula(temporary_r) * 255.0;
    value_type green = formula(temporary_g) * 255.0;
    value_type blue = formula(temporary_b) * 255.0;

    return Color(static_cast<uint8_t>(red),
        static_cast<uint8_t>(green),
        static_cast<uint8_t>(blue),
        alpha);
}

HslColor::value_type HslColor::hue() const
{
    return m_hue;
}

HslColor::value_type HslColor::saturation() const
{
    return m_saturation;
}

HslColor::value_type HslColor::luminance() const
{
    return m_luminance;
}

void HslColor::setHue(value_type hue)
{

    // TODO: write correct asserts for 'setHue/Saturation/Luminance' and 'rotateHue'
    //REQUIRE(TAG, saturation >= 0.0 && saturation <= 360.0, "hue out of bounds");

    m_hue = hue;
}

void HslColor::setSaturation(value_type saturation)
{

    //REQUIRE(TAG, saturation >= 0.0 && saturation <= 100.0, "saturation out of bounds");

    m_saturation = saturation;
}

void HslColor::setLuminance(value_type luminance)
{

    //REQUIRE(TAG, luminance >= 0.0 && luminance <= 100.0, "luminance out of bounds");

    m_luminance = luminance;
}

void HslColor::rotateHue(value_type shift)
{

    //REQUIRE(TAG, shift >= 0.0, "only positive shift for now");

    m_hue += shift;

    while (m_hue > 360.0) {

        m_hue -= 360.0;
    }
}

void HslColor::addSaturation(value_type shift)
{

    m_saturation += shift;

    if (m_saturation > 1.0)
        m_saturation = 1.0;
    if (m_saturation < 0.0)
        m_saturation = 0.0;
}

void HslColor::addLuminance(value_type shift)
{

    m_luminance += shift;
    if (m_luminance > 1.0)
        m_luminance = 1.0;
    if (m_luminance < 0.0)
        m_luminance = 0.0;
}
