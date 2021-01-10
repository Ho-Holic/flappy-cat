#ifndef FLAPPY_CAT_FLAPPYCATCOLORSCHEME_H
#define FLAPPY_CAT_FLAPPYCATCOLORSCHEME_H

// game
#include <core/Color.hpp>

// stl
#include <random>
#include <vector>

enum class Daytime;

class FlappyCatColorScheme {
public:
  enum Colors : size_t;

public:
  FlappyCatColorScheme();

public:
  Color random() const;
  void generateNewScheme(Daytime daytime);
  Color operator[](Colors index) const;

private:
  void generateDayScheme();
  void generateNightScheme();

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
  MascotBodyColor,
  MascotScarfColor,
  MascotMouthColor,
  TextColor,

  ColorsSize
};


#endif //FLAPPY_CAT_FLAPPYCATCOLORSCHEME_H
