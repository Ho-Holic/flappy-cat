// self
#include "FlappyCatGame.h"
#include "Log.h"

// stl
#include <algorithm>

FlappyCatGame::FlappyCatGame()
: mColorScheme()
, mGameConstants()
, mGameState(PressButtonState)
, mPlateWidth(0.f)
, mFloor(Position(0.f, 0.f), Position(0.f, 0.f))
, mFloorSpikes()
, mTopBlocks()
, mBottomBlocks()
, mBackgroundDirt(Position(0.f, 0.f), Position(0.f, 0.f))
, mBackgroundCity()
, mBackgroundSky()
, mBall() {
  initialize();
  reset();
}

void FlappyCatGame::initialize() {

  mPlateWidth = mGameConstants.plateWidth();

  // create main game obstacles

  // floor
  mFloor.transformation().setPosition(Position(-mPlateWidth, -800.f));
  mFloor.geometry().resize(Position(mPlateWidth * 2.f, 20.f));
  mFloor.setColor(mColorScheme.block());

  // floor spikes (for movement effect)
  Position spikeSize(mGameConstants.spikeSize());

  mFloorSpikes.reserve(120);

  size_t spikeCount = static_cast<size_t>(mPlateWidth / spikeSize.x());

  for (size_t i = 0; i < spikeCount;  ++i) {

    mFloorSpikes.emplace_back(Position(0.f, 0.f), spikeSize);
  }

  // moving blocks
  Position blockSize(mGameConstants.blockSize());

  mTopBlocks.reserve(120);
  mBottomBlocks.reserve(120);

  size_t blockCount = static_cast<size_t>(mPlateWidth / blockSize.x());

  for (size_t i = 0; i < blockCount; ++i) {

    mTopBlocks   .emplace_back(Position(0.f, 0.f), blockSize);
    mBottomBlocks.emplace_back(Position(0.f, 0.f), blockSize);
  }

  // create background decoration stuff

  // dirt under floor
  mBackgroundDirt.transformation().setPosition(Position(-mPlateWidth, -900.f));
  mBackgroundDirt.geometry().resize(Position(mPlateWidth * 2.f, 100.f));
  mBackgroundDirt.setColor(mColorScheme.dirt());

  // city buildings
  Position houseSize(mGameConstants.houseSize());

  mBackgroundCity.reserve(120);

  size_t houseCount = static_cast<size_t >(mPlateWidth / houseSize.x()) * 2;

  for (size_t i = 0; i < houseCount; ++i) {

    Position varyingSize(houseSize + Position(0.f, mGameConstants.randomOffsetFrom(0.f, 200.f)));
    mBackgroundCity.emplace_back(Position(0.f, 0.f), varyingSize);
  }

  // sky with clouds
  mBackgroundSky.reserve(120);

  size_t cloudCount = 100;

  for (size_t i = 0; i < cloudCount; ++i) {
    mBackgroundSky.emplace_back(Position(0.f, 0.f), 50.f, 32);
  }

}

void FlappyCatGame::reset() {

  mColorScheme.generateNewScheme();

  mGameState = PressButtonState;

  // place ball
  mBall.geometry().setRadius(mGameConstants.ballRadius());
  mBall.transformation().setPosition(Position(0.f, 0.f));
  mBall.setColor(mColorScheme.ball());

  // place blocks
  Position::position_type blockWidth = mGameConstants.blockSize().x();
  Position::position_type gapInterval = mGameConstants.gapInterval();

  REQUIRE(TAG, mTopBlocks.size() == mBottomBlocks.size(), "Blocks must be in sync");

  for (size_t i = 0; i < mTopBlocks.size(); ++i) {

    float offsetX = (mPlateWidth + i * 2.f * blockWidth);
    float offsetY = mGameConstants.randomOffsetFrom(0.f, 200.f);

    mTopBlocks   [i].transformation().setPosition(Position(offsetX, offsetY + gapInterval));
    mBottomBlocks[i].transformation().setPosition(Position(offsetX, offsetY - gapInterval));

    mTopBlocks   [i].setColor(mColorScheme.block());
    mBottomBlocks[i].setColor(mColorScheme.block());
  }

  // place background

  // place spikes

  Position::position_type spikeWidth = mGameConstants.spikeSize().x();

  for (size_t i = 0; i < mFloorSpikes.size(); ++i) {

    Position pos(-mPlateWidth + i * 2.f * spikeWidth, -825.f);

    mFloorSpikes[i].transformation().setPosition(pos);
    mFloorSpikes[i].setColor(mColorScheme.block());
  }

  // city buildings
  Position::position_type houseWidth = mGameConstants.houseSize().x();

  for (size_t i = 0; i < mBackgroundCity.size(); ++i) {

    Position pos(-mPlateWidth + i * houseWidth, -800.f);

    mBackgroundCity[i].transformation().setPosition(pos);
    mBackgroundCity[i].setColor(mColorScheme.house());
  }

  // sky with clouds
  for (size_t i = 0; i < mBackgroundSky.size(); ++i) {

    mBackgroundSky[i].geometry().setRadius(mGameConstants.cloudRadius()
                                         + mGameConstants.randomOffsetFrom(0.f, 100.f));

    Position pos(mGameConstants.randomOffsetFrom(0.f, 500.f, FlappyCatGameConstants::Sign::Both),
                 mGameConstants.randomOffsetFrom(0.f, 500.f, FlappyCatGameConstants::Sign::Both));

    mBackgroundSky[i].transformation().setPosition(pos);
    mBackgroundSky[i].setColor(mColorScheme.cloud());
  }

}

void FlappyCatGame::processEvent(const AndroidEvent& event) {

  if (event.type() == TouchEventType) {

    mGameState = PlayState;

    mBall.transformation().move(Position(0.f, 200.f));
  }
}

void FlappyCatGame::update(const FrameDuration& time) {

  if (mGameState == PlayState) {

    // update ball
    mBall.transformation().move(mGameConstants.gravity());

    // update obstacles
    Position::position_type gapInterval = mGameConstants.gapInterval();

    REQUIRE(TAG, mTopBlocks.size() == mBottomBlocks.size(), "Blocks must be in sync");

    for (size_t i = 0; i < mTopBlocks.size(); ++i) {

      mTopBlocks   [i].transformation().move(Position(-10.f, 0.f));
      mBottomBlocks[i].transformation().move(Position(-10.f, 0.f));

      if (mTopBlocks[i].transformation().position().x() < ( - mPlateWidth)) {

        float offsetY = mGameConstants.randomOffsetFrom(0.f, 200.f);

        mTopBlocks[i].transformation().setPosition(Position(mPlateWidth, offsetY + gapInterval));
        mBottomBlocks[i].transformation().setPosition(Position(mPlateWidth, offsetY - gapInterval));
      }

      if (isIntersect(mBall, mTopBlocks[i])
      ||  isIntersect(mBall, mBottomBlocks[i])
      ||  isIntersect(mBall, mFloor)) {

        mGameState = LoseState;
        Log::i(TAG, "Collide");
      }
    }

  }

  // update background

  if (mGameState != LoseState) {

    // floor spikes
    for (size_t i = 0; i < mFloorSpikes.size(); ++i) {

      mFloorSpikes[i].transformation().move(Position(-10.f, 0.f));

      if (mFloorSpikes[i].transformation().position().x() < (-mPlateWidth)) {

        Position::position_type oldY = mFloorSpikes[i].transformation().position().y();
        mFloorSpikes[i].transformation().setPosition(Position(mPlateWidth, oldY));
      }
    }

    // clouds
    for (size_t i = 0; i < mBackgroundCity.size(); ++i) {

      mBackgroundCity[i].transformation().move(Position(-5.f, 0.f));

      if (mBackgroundCity[i].transformation().position().x() < (-mPlateWidth)) {

        Position::position_type oldY = mBackgroundCity[i].transformation().position().y();
        mBackgroundCity[i].transformation().setPosition(Position(mPlateWidth, oldY));
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

void FlappyCatGame::render(const AndroidWindow& window) {

  window.clear(mColorScheme.background());

  for (const CircleShape& cloud    : mBackgroundSky)  window.draw(cloud);
  for (const RectangleShape& house : mBackgroundCity) window.draw(house);

  window.draw(mBackgroundDirt);

  for (const RectangleShape& block : mTopBlocks)      window.draw(block);
  for (const RectangleShape& block : mBottomBlocks)   window.draw(block);
  for (const RectangleShape& spike : mFloorSpikes)    window.draw(spike);

  window.draw(mFloor);
  window.draw(mBall);

  window.display();
}
