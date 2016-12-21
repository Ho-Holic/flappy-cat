#ifndef FLAPPY_CAT_FLAPPYCATCOLORSCHEME_H
#define FLAPPY_CAT_FLAPPYCATCOLORSCHEME_H

// self
#include <core/Color.h>

// stl
#include <vector>

class FlappyCatColorScheme {
public:
  enum Colors : uint32_t;

public:
  FlappyCatColorScheme();

public:
  void generateNewScheme();
  Color random();

public:
  Color background() const;
  Color block() const;
  Color ball() const;

private:
  std::vector<Color> mScheme;
};

enum FlappyCatColorScheme::Colors : uint32_t {
  Background,
  Block,
  Ball,
  ColorsSize
};


#endif //FLAPPY_CAT_FLAPPYCATCOLORSCHEME_H
