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

    mBall.transformation().move(Position(0.f, 200.f));
  }
}

void FlappyCatGame::update(const FrameDuration& time) {

  if (mGameState == PlayState) {

    mBall.transformation().move(Position(0.f, -10.f));

    Position::position_type blockWidth = 300.f;
    Position::position_type gapHeight = 300.f;

    REQUIRE(TAG, mTopBlocks.size() == mBottomBlocks.size(), "Blocks must be in sync");

    for (size_t i = 0; i < mTopBlocks.size(); ++i) {

      mTopBlocks   [i].transformation().move(Position(-5.f, 0.f));
      mBottomBlocks[i].transformation().move(Position(-5.f, 0.f));

      if (mTopBlocks[i].transformation().position().x() < ( - mPlateSize)) {

        float offsetY = randomPositionFrom(0.f);

        mTopBlocks[i].transformation().setPosition(Position(mPlateSize, offsetY + gapHeight));
        mBottomBlocks[i].transformation().setPosition(Position(mPlateSize, offsetY - gapHeight));
      }

      if (isIntersect(mBall, mTopBlocks[i]) || isIntersect(mBall, mBottomBlocks[i])) {

        mGameState = PressButtonState;
        Log::i(TAG, "Collide");
      }
    }
  }
}

bool FlappyCatGame::isIntersect(const CircleShape& circle, const RectangleShape& rect) const {

  float radius = circle.geometry().radius();
  // circle origin in bottom left so we shift by radius
  Position center = circle.transformation().position() + Position(radius, radius);

  REQUIRE(TAG, rect.geometry().points() == 4, "Rect must have four points");
  Position a = rect.transformation().position() + rect.geometry().pointAt(0);
  Position b = rect.transformation().position() + rect.geometry().pointAt(1);
  Position c = rect.transformation().position() + rect.geometry().pointAt(2);
  Position d = rect.transformation().position() + rect.geometry().pointAt(3);

  auto dot = [](const Position& a, const Position& b) {
    return a.x() * b.x() + a.y() * b.y();
  };

  auto isPointInRect = [&dot](const Position& p,
                          const Position& a,
                          const Position& b,
                          const Position& c,
                          const Position& d) {

    auto apab = dot(p - a, b - a);
    auto ab2  = dot(b - a, b - a);
    auto apad = dot(p - a, d - a);
    auto ad2  = dot(d - a, d - a);

    return (0 <= apab && apab <= ab2)
        && (0 <= apad && apad <= ad2);
  };

  auto isLineInCircle = [&dot](const Position& p,
                           float r,
                           const Position& a,
                           const Position& b) {

    Position c = b - a;
    Position::position_type factor = dot(c, p-a) / (c.x() * c.x() + c.y() * c.y());

    Position d = (c * factor) + a; // `d` is projection of `p` on `ab`

    auto distance = [](const Position& a, const Position& b) {
      return std::sqrt((a.x() - b.x()) * (a.x() - b.x())
                     + (a.y() - b.y()) * (a.y() - b.y()));
    };

    auto distanceAB = distance(a, b);
    auto distanceAD = distance(a, d);
    auto distanceDB = distance(d, b);

    bool isPointInLine = distanceAD + distanceDB <= distanceAB;

    return isPointInLine && (distance(p, d) <= r);
  };

  return isPointInRect (center, a, b, c, d)
      || isLineInCircle(center, radius, a, b)
      || isLineInCircle(center, radius, b, c)
      || isLineInCircle(center, radius, c, d)
      || isLineInCircle(center, radius, d, a);
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
