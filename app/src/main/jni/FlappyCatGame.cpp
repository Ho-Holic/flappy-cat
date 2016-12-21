// self
#include "FlappyCatGame.h"

// stl
#include <random>

FlappyCatGame::FlappyCatGame()
: mColorScheme()
, mGameState(PressButtonState)
, mPlateSize(1000.f)
, mBlocks()
, mBall() {
  reset();
}

void FlappyCatGame::reset() {

  mColorScheme.generateNewScheme();

  mGameState = PressButtonState;

  // add ball
  mBall.geometry().setRadius(50.f);
  mBall.transformation().setPosition(Position(0.f, 0.f));
  mBall.setColor(mColorScheme.ball());

  // add blocks
  Position::position_type blockWidth = 300.f;

  size_t blockCount = static_cast<size_t >(mPlateSize / blockWidth);

  mBlocks.reserve(120);

  for (size_t i = 0; i < blockCount; ++i) {

    float offsetX = (mPlateSize + i * 2.f * blockWidth);
    float offsetY = randomPositionFrom(0.f);


    mBlocks.emplace_back(Position(offsetX, offsetY + blockWidth),
                         Position(blockWidth, 200.f)); // top

    mBlocks.emplace_back(Position(offsetX, offsetY - blockWidth),
                         Position(blockWidth, 200.f)); // bottom
  }

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

      block.transformation().move(Position(-5.f, 0.f));

      if (block.transformation().position().x() < ( - mPlateSize)) {

        block.transformation().setPosition(Position(mPlateSize,
                                                    block.transformation().position().y()));
      }

    }
  }
}


Position::position_type FlappyCatGame::randomPositionFrom(Position::position_type initial) {

  std::random_device rd;
  std::mt19937 gen(rd());

  std::normal_distribution<float> d(initial, 200.f);

  return d(gen);
}

void FlappyCatGame::render(const AndroidWindow& window) {

  window.clear(mColorScheme.background());

  for(const RectangleShape& block : mBlocks) {
    window.draw(block);
  }

  window.draw(mBall);

  window.display();
}
