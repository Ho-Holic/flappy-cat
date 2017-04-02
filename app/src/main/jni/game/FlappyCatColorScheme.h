#ifndef FLAPPY_CAT_FLAPPYCATCOLORSCHEME_H
#define FLAPPY_CAT_FLAPPYCATCOLORSCHEME_H

// game
#include <core/Color.h>

// stl
#include <random>
#include <vector>

class FlappyCatColorScheme {
public:
  enum Colors : size_t;

public:
  FlappyCatColorScheme();

public:
  Color random() const;
  void generateNewScheme();

public:
  Color background() const;
  Color block()      const;
  Color hero()       const;
  Color house()      const;
  Color cloud()      const;
  Color dirt()       const;

private:
  mutable std::random_device mRandomDevice;
  mutable std::mt19937 mGenerator;
  std::vector<Color> mScheme;
};

enum FlappyCatColorScheme::Colors : size_t {
  BackgroundColor,
  BlockColor,
  HeroColor,
  HouseColor,
  CloudColor,
  DirtColor,
  ColorsSize
};


#endif //FLAPPY_CAT_FLAPPYCATCOLORSCHEME_H
