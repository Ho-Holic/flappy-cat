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
, mFloor()
, mWalls()
, mBackgroundCity()
, mBackgroundSky()
, mHero() {
  initialize();
  reset();
}

void FlappyCatGame::initialize() {

  mPlateWidth = mGameConstants.plateWidth();

  // floor
  mFloor.moveTo(Position(-mPlateWidth, -800.f));
  mFloor.resize(Position(mPlateWidth * 2.f, 0.f));
  mFloor.initialize();

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

      if (wall.collideWithCircle(center, radius) || Collide::circleRect(center, radius,
                                                                        mFloor.boundingBox())) {
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

  // city buildings
  mBackgroundCity.setPosition(Position(-mPlateWidth, -800.f));
  mBackgroundCity.setSize(Position(mPlateWidth * 2.f, 0.f));
  mBackgroundCity.setLinkSize(mGameConstants.houseSize());
  mBackgroundCity.setMovementDisplacement(Position(-5.f, 0.f));

  auto adjustHouseSize = [this](FlappyCatSpike& house) {
    Position varyingSize(mGameConstants.houseSize()
                         + Position(0.f, mGameConstants.randomOffsetFrom(0.f, 200.f)));
    house.resize(varyingSize);
  };

  mBackgroundCity.setResetModifier(adjustHouseSize);
  mBackgroundCity.setWrapAroundModifier(adjustHouseSize);
  mBackgroundCity.initialize();

  // sky with clouds
  mBackgroundSky.setResetModifier(
    [this](FlappyCatCloud::entity_type& cloud) {
      cloud.geometry().setRadius(mGameConstants.cloudRadius()
                               + mGameConstants.randomOffsetFrom(0.f, 100.f));

      Position pos(mGameConstants.randomOffsetFrom(0.f, 500.f, FlappyCatGameConstants::Sign::Both),
                   mGameConstants.randomOffsetFrom(0.f, 500.f, FlappyCatGameConstants::Sign::Both));

      cloud.transformation().setPosition(pos);
      cloud.setColor(mColorScheme.cloud());
    }
  );
  mBackgroundSky.initialize();
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

  // place floor
  mFloor.setColor(mColorScheme.block());
  mFloor.reset();

  // city buildings
  mBackgroundCity.setColor(mColorScheme.house());
  mBackgroundCity.reset();

  // sky with clouds
  mBackgroundSky.reset();

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

    mFloor.update(time);
    mBackgroundCity.update(time);
  }
}

void FlappyCatGame::render(const Window& window) const {

  window.clear(mColorScheme.background());

  mBackgroundSky.drawOn(window);
  mBackgroundCity.drawOn(window);
  mFloor.drawOn(window);
  mWalls.drawOn(window);
  mHero.drawOn(window);

  window.display();
}
