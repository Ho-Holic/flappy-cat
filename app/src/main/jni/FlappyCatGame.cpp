// self
#include "FlappyCatGame.h"
#include "Log.h"

// stl
#include <random>
#include <algorithm>

FlappyCatGame::FlappyCatGame()
: mColorScheme()
, mGameState(PressButtonState)
, mPlateSize(1000.f)
, mTopBlocks()
, mBottomBlocks()
, mBall() {
  initialize();
  reset();
}

void FlappyCatGame::initialize() {

  Position::position_type blockWidth = 300.f;
  Position::position_type blockHeight = 200.f;

  size_t blockCount = static_cast<size_t >(mPlateSize / blockWidth);

  mTopBlocks.reserve(120);
  mBottomBlocks.reserve(120);

  for (size_t i = 0; i < blockCount; ++i) {

    mTopBlocks.emplace_back(Position(0.f, 0.f), Position(blockWidth, blockHeight));
    mBottomBlocks.emplace_back(Position(0.f, 0.f), Position(blockWidth, blockHeight));
  }

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
  Position::position_type gapHeight = 300.f;

  REQUIRE(TAG, mTopBlocks.size() == mBottomBlocks.size(), "Blocks must be in sync");

  for (size_t i = 0; i < mTopBlocks.size(); ++i) {

    float offsetX = (mPlateSize + i * 2.f * blockWidth);
    float offsetY = randomPositionFrom(0.f);

    mTopBlocks   [i].transformation().setPosition(Position(offsetX, offsetY + gapHeight));
    mBottomBlocks[i].transformation().setPosition(Position(offsetX, offsetY - gapHeight));

    mTopBlocks   [i].setColor(mColorScheme.block());
    mBottomBlocks[i].setColor(mColorScheme.block());
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

    Log::i(TAG, "--------------------");

    Position::position_type blockWidth = 300.f;
    Position::position_type gapHeight = 300.f;

    REQUIRE(TAG, mTopBlocks.size() == mBottomBlocks.size(), "Blocks must be in sync");

    for (size_t i = 0; i < mTopBlocks.size(); ++i) {

      Log::i(TAG, "Block (%g, %g)", mTopBlocks   [i].transformation().position().x(),
                                    mTopBlocks   [i].transformation().position().y());
      Log::i(TAG, "Block (%g, %g)", mBottomBlocks[i].transformation().position().x(),
                                    mBottomBlocks[i].transformation().position().y());

      mTopBlocks   [i].transformation().move(Position(-5.f, 0.f));
      mBottomBlocks[i].transformation().move(Position(-5.f, 0.f));

      if (mTopBlocks[i].transformation().position().x() < ( - mPlateSize)) {

        float offsetY = randomPositionFrom(0.f);

        mTopBlocks[i].transformation().setPosition(Position(mPlateSize, offsetY + gapHeight));
        mBottomBlocks[i].transformation().setPosition(Position(mPlateSize, offsetY - gapHeight));
      }

      //if (isIntersect(mBall, block)) {

      //  Log::i(TAG, "Collide");
      //}
    }
  }
}

bool FlappyCatGame::isIntersect(const CircleShape& circle, const RectangleShape& rect) const {

  //Log::i(TAG, "Circle (%g, %g)", circle.transformation().position().x(),
  //                               circle.transformation().position().y());

  //Log::i(TAG, "Rect (%g, %g)", rect.transformation().position().x(),
  //                             rect.transformation().position().y());

  return false;

  // helper functions
  auto componentAt = [](size_t i, const Position& p) {

    return i == 0 ? p.x() : p.y();
  };

  auto square = [](float r) {
    return r * r;
  };

  using CompareFunction = std::function<bool(Position::position_type, Position::position_type)>;

  auto lessPredicate = [](Position::position_type a, Position::position_type b) {
    return a < b;
  };

  auto greaterPredicate = [](Position::position_type a, Position::position_type b) {
    return a > b;
  };

  auto targetPoint = [](const Geometry& geometry, CompareFunction predicate) -> Position {

    REQUIRE(TAG, geometry.points() > 0, "We need some points here");

    Position::position_type targetX = geometry.pointAt(0).x();
    Position::position_type targetY = geometry.pointAt(0).y();

    for (Geometry::size_type i = 1; i < geometry.points(); ++i) {

      Position::position_type x = geometry.pointAt(i).x();
      Position::position_type y = geometry.pointAt(i).y();

      if (predicate(x, targetX)) targetX = x;
      if (predicate(y, targetY)) targetY = y;
    }

    return Position(targetX, targetY);
  };

  enum Dimension : size_t { Dimension2d = 2 };


  // main algorithm
  Position::position_type dmin = 0.f;

  const Geometry& geometry = rect.geometry();

  Position bmin = targetPoint(geometry, lessPredicate);
  Position bmax = targetPoint(geometry, greaterPredicate);

  for (size_t i = 0; i < Dimension2d; ++i) {

    Position::position_type c = componentAt(i, circle.transformation().position());

    if      (c < componentAt(i, bmin)) dmin += square(c - componentAt(i, bmin));
    else if (c > componentAt(i, bmax)) dmin += square(c - componentAt(i, bmax));

  }

  return dmin <= square(circle.geometry().radius());
}


Position::position_type FlappyCatGame::randomPositionFrom(Position::position_type initial) {

  std::random_device rd;
  std::mt19937 gen(rd());

  std::normal_distribution<float> d(initial, 200.f);

  return d(gen);
}

void FlappyCatGame::render(const AndroidWindow& window) {

  window.clear(mColorScheme.background());

  for (const RectangleShape& block : mTopBlocks)    window.draw(block);
  for (const RectangleShape& block : mBottomBlocks) window.draw(block);

  window.draw(mBall);

  window.display();
}
