#ifndef FLAPPY_CAT_FLAPPYCATGAME_H
#define FLAPPY_CAT_FLAPPYCATGAME_H

// self
#include <core/Clock.h>
#include <android/AndroidEvent.h>
#include <android/AndroidWindow.h>
#include <prototype/RectangleShape.h>
#include <prototype/CircleShape.h>
#include <FlappyCatColorScheme.h>

// stl
#include <vector>
#include <memory>

class FlappyCatGame {
public:
  FlappyCatGame();

public:
  void processEvent(const AndroidEvent& event);
  void update(const FrameDuration& time);
  void render(const AndroidWindow&);

private:
  enum GameState : int32_t;

private:
  void initialize();
  void reset();
  Position::position_type randomPositionFrom(Position::position_type initial);
  bool isIntersect(const CircleShape& circle, const RectangleShape& rect) const;

private:
  FlappyCatColorScheme mColorScheme;
  GameState mGameState;
  Position::position_type mPlateSize;
  std::vector<RectangleShape> mTopBlocks;
  std::vector<RectangleShape> mBottomBlocks;
  CircleShape mBall;
};

enum FlappyCatGame::GameState : int32_t {
  PressButtonState,
  PlayState,
  LoseState
};


#endif //FLAPPY_CAT_FLAPPYCATGAME_H
