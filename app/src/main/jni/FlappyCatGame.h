#ifndef FLAPPY_CAT_FLAPPYCATGAME_H
#define FLAPPY_CAT_FLAPPYCATGAME_H

// engine
#include <core/Clock.h>
#include <core/Event.h>
#include <core/Window.h>
#include <prototype/RectangleShape.h>

// self
#include "FlappyCatColorScheme.h"
#include "FlappyCatGameConstants.h"
#include "FlappyCatWall.h"
#include "FlappyCatChain.h"
#include "FlappyCatSpike.h"
#include "FlappyCatHero.h"

// stl
#include <vector>
#include <memory>
#include <cmath>

class FlappyCatGame {
public:
  FlappyCatGame();

public:
  void processEvent(const Event& event);
  void update(const FrameDuration& time);
  void render(const Window&) const;

private:
  enum GameState : int32_t;

private:
  void initialize();
  void reset();


private:
  FlappyCatColorScheme mColorScheme;
  FlappyCatGameConstants mGameConstants;
  GameState mGameState;
  Position::position_type mPlateWidth;
  RectangleShape mFloor;
  FlappyCatChain<FlappyCatSpike> mFloorSpikes;
  FlappyCatChain<FlappyCatWall> mWalls;
  RectangleShape mBackgroundDirt;
  FlappyCatChain<FlappyCatSpike> mBackgroundCity;
  std::vector<CircleShape>    mBackgroundSky;
  FlappyCatHero mHero;
};

enum FlappyCatGame::GameState : int32_t {
  PressButtonState,
  PlayState,
  LoseState
};


#endif //FLAPPY_CAT_FLAPPYCATGAME_H
