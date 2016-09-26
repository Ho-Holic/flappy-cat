#ifndef FLAPPY_CAT_ANDROIDCOLOR_H
#define FLAPPY_CAT_ANDROIDCOLOR_H

// stl
#include <cstdint>

class AndroidColor {
public:
  AndroidColor();
  AndroidColor(uint32_t rgbaColor);

public:
  uint8_t r() const;
  uint8_t g() const;
  uint8_t b() const;
  uint8_t alpha() const;

private:
  uint8_t mRed;
  uint8_t mGreen;
  uint8_t mBlue;
  uint8_t mAlpha;
};


#endif //FLAPPY_CAT_ANDROIDCOLOR_H
