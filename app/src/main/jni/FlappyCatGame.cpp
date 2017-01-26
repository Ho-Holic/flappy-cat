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

  // spikes (movement effect)
  mFloorSpikes.setPosition(Position(0.f, -825.f));
  mFloorSpikes.setSize(Position(mPlateWidth, 0.f));
  mFloorSpikes.setLinkSize(mGameConstants.spikeSize());
  mFloorSpikes.setMovementDisplacement(Position(-10.f, 0.f));
  mFloorSpikes.initialize();

  // moving blocks
  Position blockSize(mGameConstants.blockSize());

  // TODO: parametrize reserve function
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

  // TODO: parametrize reserve function
  mBackgroundCity.reserve(120);

  size_t houseCount = static_cast<size_t >(mPlateWidth / houseSize.x()) * 2;

  for (size_t i = 0; i < houseCount; ++i) {

    Position varyingSize(houseSize + Position(0.f, mGameConstants.randomOffsetFrom(0.f, 200.f)));
    mBackgroundCity.emplace_back(Position(0.f, 0.f), varyingSize);
  }

  // sky with clouds
  // TODO: parametrize reserve function
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
  mFloorSpikes.setColor(mColorScheme.block());
  mFloorSpikes.reset();

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

      Position p = mWalls[i].position();

      if (p.x() < -mPlateWidth) {

        mWalls[i].setGapDisplacement(mGameConstants.randomOffsetFrom(0.f, 200.f));
        mWalls[i].setPosition(Position(p.x() + mPlateWidth * 2.f, p.y()));
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
    mFloorSpikes.update(time);

    // clouds
    for (size_t i = 0; i < mBackgroundCity.size(); ++i) {

      mBackgroundCity[i].transformation().move(Position(-5.f, 0.f));

      Position p = mBackgroundCity[i].transformation().position();

      if (p.x() < (-mPlateWidth)) {

        mBackgroundCity[i].transformation().setPosition(Position(p.x() + mPlateWidth * 2.f, p.y()));
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

  mFloorSpikes.drawOn(window);

  window.draw(mFloor);
  window.draw(mBall);

  window.display();
}
