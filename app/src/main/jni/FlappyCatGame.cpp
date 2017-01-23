// self
#include "FlappyCatGame.h"
#include "Log.h"
#include <physics/Collide.h>


FlappyCatGame::FlappyCatGame()
: mColorScheme()
, mGameConstants()
, mGameState(PressButtonState)
, mPlateWidth(0.f)
, mFloor(Position(0.f, 0.f), Position(0.f, 0.f))
, mFloorSpikes()
, mWalls()
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

  mWalls.reserve(120);

  size_t blockCount = static_cast<size_t>(mPlateWidth / blockSize.x());

  for (size_t i = 0; i < blockCount; ++i) {

    mWalls.emplace_back(Position(0.f, 0.f), blockSize);
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

  for (size_t i = 0; i < mWalls.size(); ++i) {

    float x = mPlateWidth + i * 2.f * blockWidth;
    float y = 0.f;

    mWalls[i].setGapInterval(mGameConstants.gapInterval());
    mWalls[i].setGapDisplacement(mGameConstants.randomOffsetFrom(0.f, 200.f));
    mWalls[i].setPosition(Position(x, y));

    mWalls[i].setColor(mColorScheme.block());
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


    for (size_t i = 0; i < mWalls.size(); ++i) {

      mWalls[i].update(time);

      if (mWalls[i].position().x() < -mPlateWidth) {

        mWalls[i].setGapDisplacement(mGameConstants.randomOffsetFrom(0.f, 200.f));
        mWalls[i].setPosition(Position(mPlateWidth, mWalls[i].position().y()));
      }

      float radius = mBall.geometry().radius();
      // TODO: implement proper origin in `transformation` and remove this code
      // circle origin in bottom left so we shift by radius
      Position center = mBall.transformation().position() + Position(radius, radius);


      if (mWalls[i].collideWithCircle(center, radius)
      ||  Collide::circleRect(center, radius, mFloor)) {

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

void FlappyCatGame::render(const AndroidWindow& window) const {

  window.clear(mColorScheme.background());

  for (const CircleShape& cloud    : mBackgroundSky)  window.draw(cloud);
  for (const RectangleShape& house : mBackgroundCity) window.draw(house);

  window.draw(mBackgroundDirt);

  for (const FlappyCatWall& wall   : mWalls)       wall.drawOn(window);
  for (const RectangleShape& spike : mFloorSpikes) window.draw(spike);

  window.draw(mFloor);
  window.draw(mBall);

  window.display();
}
