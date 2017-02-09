#ifndef FLAPPY_CAT_FLAPPYCATCOLORSCHEME_H
#define FLAPPY_CAT_FLAPPYCATCOLORSCHEME_H

// self
#include <core/Color.h>

// stl
#include <random>
#include <vector>

class FlappyCatColorScheme {
public:
  enum Colors : uint32_t;

public:
  FlappyCatColorScheme();

public:
  Color random();
  void generateNewScheme();

public:
  Color background() const;
  Color block()      const;
  Color hero()       const;
  Color house()      const;
  Color cloud()      const;
  Color dirt()       const;

private:
  std::random_device mRandomDevice;
  std::mt19937 mGenerator;
  std::vector<Color> mScheme;
};

enum FlappyCatColorScheme::Colors : uint32_t {
  Background,
  Block,
  Hero,
  House,
  Cloud,
  Dirt,
  ColorsSize
};


#endif //FLAPPY_CAT_FLAPPYCATCOLORSCHEME_H
