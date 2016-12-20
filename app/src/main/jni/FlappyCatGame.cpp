// self
#include "FlappyCatGame.h"

FlappyCatGame::FlappyCatGame()
: mColorScheme()
, mGameState(PressButtonState)
, mPlateSize(500.f)
, mBlocks()
, mBall() {
  reset();
}

void FlappyCatGame::reset() {

  mColorScheme.generateNewScheme();

  mGameState = PressButtonState;

  mBall.geometry().setRadius(50.f);
  mBall.transformation().setPosition(Position(0.f, 0.f));
  mBall.setColor(mColorScheme.ball());

  mBlocks.reserve(20);
  mBlocks.emplace_back(Position(-150.f, 600.f), Position(400.f, 100.f));
  mBlocks.emplace_back(Position(-150.f, -1000.f), Position(400.f, 100.f));

  for (RectangleShape& block : mBlocks) {
    block.setColor(mColorScheme.block());
  }
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

    for (RectangleShape& block : mBlocks) {

      block.transformation().move(Position(-10.f, 0.f));

      if (block.transformation().position().x() < ( - mPlateSize)) {

        block.transformation().setPosition(Position(mPlateSize,
                                                    block.transformation().position().y()));
      }

    }
  }
}

void FlappyCatGame::render(const AndroidWindow& window) {

  window.clear(mColorScheme.background());

  for(const RectangleShape& block : mBlocks) {
    window.draw(block);
  }

  window.draw(mBall);

  window.display();
}




