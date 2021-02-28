// engine
#include "Color.hpp"

// stl
#include <algorithm>

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha)
    : mRed(r)
    , mGreen(g)
    , m_blue(b)
    , m_alpha(alpha)
{
    //
}

Color::Color(uint8_t r, uint8_t g, uint8_t b)
    : Color(r, g, b, 255)
{
    //
}

Color::Color()
    : Color(0, 0, 0, 255)
{
    //
}

Color::Color(uint32_t rgbaColor)
    : Color(
        static_cast<uint8_t>((rgbaColor & 0xFF000000) >> 24),
        static_cast<uint8_t>((rgbaColor & 0x00FF0000) >> 16),
        static_cast<uint8_t>((rgbaColor & 0x0000FF00) >> 8),
        static_cast<uint8_t>((rgbaColor & 0x000000FF) >> 0))
{
    //
}

uint8_t Color::r() const
{
    return mRed;
}

uint8_t Color::g() const
{
    return mGreen;
}

uint8_t Color::b() const
{
    return m_blue;
}

uint8_t Color::alpha() const
{
    return m_alpha;
}

Color Color::grayscale() const
{

    // explicit integer promotion 'int(mRed)'

    uint8_t mid = static_cast<uint8_t>((int(mRed) + mGreen + m_blue) / 3);
    return Color(mid, mid, mid, 255);
}

Color& Color::operator*=(Color::value_type factor)
{
    mRed = static_cast<uint8_t>(mRed * factor);
    mGreen = static_cast<uint8_t>(mGreen * factor);
    m_blue = static_cast<uint8_t>(m_blue * factor);
    // alpha does not change
    return *this;
}

// free functions

Color operator+(const Color& left, const Color& right)
{

    // explicit integer promotion 'int(left.mRed)'

    return Color(uint8_t(std::min(int(left.mRed) + right.mRed, 255)),
        uint8_t(std::min(int(left.mGreen) + right.mGreen, 255)),
        uint8_t(std::min(int(left.m_blue) + right.m_blue, 255)),
        uint8_t(std::min(int(left.m_alpha) + right.m_alpha, 255)));
}

Color operator-(const Color& left, const Color& right)
{

    // explicit integer promotion 'int(left.mRed)'

    return Color(uint8_t(std::max(int(left.mRed) - right.mRed, 0)),
        uint8_t(std::max(int(left.mGreen) - right.mGreen, 0)),
        uint8_t(std::max(int(left.m_blue) - right.m_blue, 0)),
        uint8_t(std::max(int(left.m_alpha) - right.m_alpha, 0)));
}

Color operator*(const Color& left, const Color& right)
{

    // explicit integer promotion 'int(left.mRed)'

    return Color(uint8_t(int(left.mRed) * right.mRed / 255),
        uint8_t(int(left.mGreen) * right.mGreen / 255),
        uint8_t(int(left.m_blue) * right.m_blue / 255),
        uint8_t(int(left.m_alpha) * right.m_alpha / 255));
}

Color operator*(Color::value_type factor, const Color& right)
{

    return Color(right) *= factor;
}

Color operator*(const Color& left, Color::value_type factor)
{

    return Color(left) *= factor;
}
