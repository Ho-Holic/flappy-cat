// self
#include "FlappyCatGame.h"

FlappyCatGame::FlappyCatGame()
: mGameState(PressButtonState)
, mBlocks()
, mBall() {
  reset();
}

void FlappyCatGame::reset() {

  mGameState = PressButtonState;

  mBall.geometry().setRadius(50.f);
  mBall.transformation().setPosition(Position(0.f, 0.f));

  mBlocks.reserve(20);
  mBlocks.emplace_back(Position(-150.f, 600.f), Position(400.f, 100.f));
  mBlocks.emplace_back(Position(-150.f, -1000.f), Position(400.f, 100.f));
}

void FlappyCatGame::processEvent(const AndroidEvent& event) {

  if (event.type() == TouchEventType) {

    if (mGameState == PressButtonState) {

      mGameState = PlayState;
    }

    mBall.transformation().move(Position(0.f, 400.f));
  }
}

void FlappyCatGame::update(const FrameDuration& time) {

  if (mGameState == PlayState) {

    mBall.transformation().move(Position(0.f, -10.f));
  }
}

void FlappyCatGame::render(const AndroidWindow& window) {

  window.clear(Color(255, 255, 255));

  for(const RectangleShape& block : mBlocks) {
    window.draw(block);
  }

  window.draw(mBall);

  window.display();
}




