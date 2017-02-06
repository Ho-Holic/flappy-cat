// self
#include "FlappyCatGame.h"

// engine
#include <core/Log.h>
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
, mHero() {
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
  mFloorSpikes.setPosition(Position(-mPlateWidth, -825.f));
  mFloorSpikes.setSize(Position(mPlateWidth * 2.f, 0.f));
  mFloorSpikes.setLinkSize(mGameConstants.spikeSize());
  mFloorSpikes.setOffset(mGameConstants.spikeSize());
  mFloorSpikes.setMovementDisplacement(Position(-10.f, 0.f));
  mFloorSpikes.initialize();

  // moving blocks
  mWalls.setPosition(Position(-mPlateWidth, 0.f));
  mWalls.setSize(Position(mPlateWidth * 2.f, 0.f));
  mWalls.setLinkSize(mGameConstants.blockSize());
  mWalls.setOffset(mGameConstants.blockSize());
  mWalls.setMovementDisplacement(Position(-10.f, 0.f));

  mWalls.setResetModifier(
    [this](FlappyCatWall& wall) {
      wall.setGapInterval(mGameConstants.gapInterval());
      wall.setGapDisplacement(mGameConstants.randomOffsetFrom(0.f, 200.f));
    }
  );

  mWalls.setUpdateModifier(
    [this](FlappyCatWall& wall) {

      float radius = mHero.radius();
      // TODO: implement proper origin in `transformation` and remove this code
      // circle origin in bottom left so we shift by radius
      Position center = mHero.position() + Position(radius, radius);

      if (wall.collideWithCircle(center, radius) || Collide::circleRect(center, radius, mFloor)) {
        mGameState = LoseState;
        Log::i(TAG, "Collide");
      }
    }
  );

  mWalls.setWrapAroundModifier(
    [this](FlappyCatWall& wall) {
      wall.setGapDisplacement(mGameConstants.randomOffsetFrom(0.f, 200.f));
    }
  );

  mWalls.initialize();

  // create background decoration stuff

  // dirt under floor
  mBackgroundDirt.transformation().setPosition(Position(-mPlateWidth, -900.f));
  mBackgroundDirt.geometry().resize(Position(mPlateWidth * 2.f, 100.f));
  mBackgroundDirt.setColor(mColorScheme.dirt());

  // city buildings
  mBackgroundCity.setPosition(Position(-mPlateWidth, -800.f));
  mBackgroundCity.setSize(Position(mPlateWidth * 2.f, 0.f));
  mBackgroundCity.setLinkSize(mGameConstants.houseSize());
  mBackgroundCity.setMovementDisplacement(Position(-5.f, 0.f));
  mBackgroundCity.initialize();

  auto adjustHouseSize = [this](FlappyCatSpike& house) {
    Position varyingSize(mGameConstants.houseSize()
                         + Position(0.f, mGameConstants.randomOffsetFrom(0.f, 200.f)));
    house.resize(varyingSize);
  };

  mBackgroundCity.setResetModifier(adjustHouseSize);
  mBackgroundCity.setWrapAroundModifier(adjustHouseSize);

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
  mHero.setRadius(mGameConstants.ballRadius());
  mHero.moveTo(Position(0.f, 0.f));
  mHero.setColor(mColorScheme.ball());

  // place blocks
  mWalls.setColor(mColorScheme.block());
  mWalls.reset();

  // place background

  // place spikes
  mFloorSpikes.setColor(mColorScheme.block());
  mFloorSpikes.reset();

  // city buildings
  mBackgroundCity.setColor(mColorScheme.house());
  mBackgroundCity.reset();

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

void FlappyCatGame::processEvent(const Event& event) {

  if (event.type() == TouchEventType) {

    mGameState = PlayState;

    mHero.moveBy(Position(0.f, 200.f));
  }
}

void FlappyCatGame::update(const FrameDuration& time) {

  if (mGameState == PlayState) {

    mHero.moveBy(mGameConstants.gravity());
    mWalls.update(time);
  }

  // update background
  if (mGameState != LoseState) {

    mFloorSpikes.update(time);
    mBackgroundCity.update(time);
  }
}

void FlappyCatGame::render(const Window& window) const {

  window.clear(mColorScheme.background());

  for (const CircleShape& cloud    : mBackgroundSky)  window.draw(cloud);

  mBackgroundCity.drawOn(window);

  window.draw(mBackgroundDirt);

  mWalls.drawOn(window);
  mFloorSpikes.drawOn(window);

  window.draw(mFloor);
  mHero.drawOn(window);

  window.display();
}
