#ifndef FLAPPY_CAT_FLAPPYCATGAME_H
#define FLAPPY_CAT_FLAPPYCATGAME_H

// engine
#include <core/Clock.h>
#include <core/Event.h>
#include <core/Window.h>
#include <prototype/RectangleShape.h>

// game
#include "FlappyCatGameConstants.h"
#include "entity/FlappyCatWall.h"
#include "entity/FlappyCatChain.h"
#include "entity/FlappyCatSpike.h"
#include "entity/FlappyCatHero.h"
#include "entity/FlappyCatCloud.h"
#include "entity/FlappyCatFloor.h"
#include "entity/FlappyCatViewLimit.h"
#include "entity/FlappyCatBackground.h"

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
  Position cameraSize() const;

private:
  enum GameState : int32_t;

private:
  void initialize();
  void reset();

private:
  FlappyCatGameConstants mGameConstants;
  GameState mGameState;
  FlappyCatBackground mBackground;
  FlappyCatFloor mFloor;
  FlappyCatChain<FlappyCatWall> mBarricade;
  FlappyCatChain<FlappyCatSpike> mBackgroundCity;
  FlappyCatCloud mBackgroundSky;
  FlappyCatHero mHero;
  FlappyCatViewLimit mLimit;
};

enum FlappyCatGame::GameState : int32_t {
  PressButtonState,
  PlayState,
  LoseState,
  OnTheFloorState
};

#endif //FLAPPY_CAT_FLAPPYCATGAME_H
