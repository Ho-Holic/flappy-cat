#ifndef FLAPPY_CAT_ANDROIDCOLOR_H
#define FLAPPY_CAT_ANDROIDCOLOR_H

// stl
#include <cstdint>

class Color {
public:
  static Color random();

public:
  Color(uint8_t r, uint8_t g, uint8_t b);
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);
  Color();
  Color(uint32_t rgbaColor);

public: // member operators
  Color& operator *= (float factor);

public: // free-function operators
  friend Color operator + (const Color& left, const Color& right);
  friend Color operator - (const Color& left, const Color& right);
  friend Color operator * (const Color& left, const Color& right);
  friend Color operator * (float factor,             const Color& right);
  friend Color operator * (const Color& left, float factor);

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


#endif //FLAPPY_CAT_ANDROIDCOLOR_H
