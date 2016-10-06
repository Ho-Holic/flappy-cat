#ifndef FLAPPY_CAT_ANDROIDCOLOR_H
#define FLAPPY_CAT_ANDROIDCOLOR_H

// stl
#include <cstdint>

class AndroidColor {
public:
  static AndroidColor random();

public:
  AndroidColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);
  AndroidColor();
  AndroidColor(uint32_t rgbaColor);

public: // member operators
  AndroidColor& operator *= (float factor);

public: // free-function operators
  friend AndroidColor operator + (const AndroidColor& left, const AndroidColor& right);
  friend AndroidColor operator - (const AndroidColor& left, const AndroidColor& right);
  friend AndroidColor operator * (const AndroidColor& left, const AndroidColor& right);
  friend AndroidColor operator * (float factor,             const AndroidColor& right);
  friend AndroidColor operator * (const AndroidColor& left, float factor);

public:
  uint8_t r() const;
  uint8_t g() const;
  uint8_t b() const;
  uint8_t alpha() const;

public:
  AndroidColor grayscale() const;

private:
  uint8_t mRed;
  uint8_t mGreen;
  uint8_t mBlue;
  uint8_t mAlpha;
};


#endif //FLAPPY_CAT_ANDROIDCOLOR_H
