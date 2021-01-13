#pragma once

// stl
#include <cstdint>

class Color {
public:
    using value_type = float;

public:
    Color(uint8_t r, uint8_t g, uint8_t b);
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);
    Color();
    Color(uint32_t rgbaColor);

public: // member operators
    Color& operator*=(value_type factor);

public: // free-function operators
    friend Color operator+(const Color& left, const Color& right);
    friend Color operator-(const Color& left, const Color& right);
    friend Color operator*(const Color& left, const Color& right);
    friend Color operator*(value_type factor, const Color& right);
    friend Color operator*(const Color& left, value_type factor);

public:
    uint8_t r() const;
    uint8_t g() const;
    uint8_t b() const;
    uint8_t alpha() const;

public:
    Color grayscale() const;

private:
    uint8_t mRed;
    uint8_t mGreen;
    uint8_t mBlue;
    uint8_t mAlpha;
};
