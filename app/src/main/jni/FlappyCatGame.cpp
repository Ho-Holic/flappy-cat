// self
#include "FlappyCatGame.h"

// engine
#include <core/Log.h>
#include <physics/Collide.h>


FlappyCatGame::FlappyCatGame()
: mGameConstants()
, mGameState(PressButtonState)
, mPlateWidth(0.f)
, mFloor(mGameConstants)
, mWalls(mGameConstants)
, mBackgroundCity(mGameConstants)
, mBackgroundSky(mGameConstants)
, mHero(mGameConstants) {
  initialize();
  reset();
}

Position FlappyCatGame::cameraSize() const {

  return mGameConstants.cameraSize();
}

void FlappyCatGame::initialize() {

  mPlateWidth = mGameConstants.plateWidth();

  // floor
  mFloor.moveTo(Position(-mPlateWidth, -800.f));
  mFloor.resize(Position(mPlateWidth * 2.f, 200.f));
  mFloor.setMovementDisplacement(Position(-10.f, 0.f));

  mFloor.setResetModifier(
    [this](FlappyCatFloor& floor) {
      floor.setColor(mGameConstants.colorScheme().block(),
                     mGameConstants.colorScheme().dirt());
    }
  );

  // moving blocks
  mWalls.moveTo(Position(-mPlateWidth, -775.f));
  mWalls.resize(Position(mPlateWidth * 2.f, 0.f));
  mWalls.setStartOffset(Position(mPlateWidth * 4.f, 0.f));
  mWalls.setLinkSize(mGameConstants.wallSize());
  mWalls.setOffsetBetweenLinks(mGameConstants.wallSize() * 2.f);
  mWalls.setMovementDisplacement(Position(-10.f, 0.f));

  mWalls.setResetModifier(
    [this](FlappyCatWall& wall) {
      wall.setGapInterval(mGameConstants.gapInterval());

      wall.setGapDisplacement(mGameConstants.clampedRandomOffsetFrom(
        0.f, 200.f,
        FlappyCatGameConstants::Sign::Both)
      );

      wall.setColor(mGameConstants.colorScheme().block());
    }
  );

  mWalls.setUpdateModifier(
    [this](FlappyCatWall& wall) {

      float radius = mHero.radius();
      // TODO: implement proper origin in 'transformation' and remove this code
      // circle origin in bottom left so we shift by radius
      Position center = mHero.position() + Position(radius, radius);

      // TODO: This type of interface? how about (collide(wall, mHero).or(wall, mFloor)){}
      if (wall.collideWithCircle(center, radius) || Collide::circleRect(center, radius,
                                                                        mFloor.boundingBox())) {
        mGameState = LoseState;
        Log::i(TAG, "Collide");
      }
    }
  );

  mWalls.setWrapAroundModifier(
    [this](FlappyCatWall& wall) {

      wall.setGapDisplacement(mGameConstants.clampedRandomOffsetFrom(
        0.f, 200.f,
        FlappyCatGameConstants::Sign::Both)
      );
    }
  );

  // city buildings
  mBackgroundCity.moveTo(Position(-mPlateWidth, -800.f));
  mBackgroundCity.resize(Position(mPlateWidth * 2.f, 0.f));
  mBackgroundCity.setLinkSize(mGameConstants.houseSize());
  mBackgroundCity.setMovementDisplacement(Position(-5.f, 0.f));

  mBackgroundCity.setResetModifier(
    [this](FlappyCatSpike& house) {
      Position varyingSize(mGameConstants.houseSize()
                           + Position(0.f, mGameConstants.randomOffsetFrom(0.f, 200.f)));
      house.resize(varyingSize);
      house.setColor(mGameConstants.colorScheme().house());
    }
  );

  mBackgroundCity.setWrapAroundModifier(
    [this](FlappyCatSpike& house) {
      Position varyingSize(mGameConstants.houseSize()
                           + Position(0.f, mGameConstants.randomOffsetFrom(0.f, 200.f)));
      house.resize(varyingSize);
    }
  );

  // sky with clouds
  mBackgroundSky.setResetModifier(
    [this](FlappyCatCloud::entity_type& cloud) {
      cloud.geometry().setRadius(mGameConstants.cloudRadius()
                               + mGameConstants.randomOffsetFrom(0.f, 100.f));

      Position pos(mGameConstants.randomOffsetFrom(0.f, 500.f, FlappyCatGameConstants::Sign::Both),
                   mGameConstants.randomOffsetFrom(0.f, 500.f, FlappyCatGameConstants::Sign::Both));

      cloud.transformation().setPosition(pos);
      cloud.setColor(mGameConstants.colorScheme().cloud());
    }
  );

  mHero.setUpdateModifier(
    [this](FlappyCatHero& hero, const FrameDuration& frameDuration) {

      hero.moveBy(hero.distance());
    }
  );

  mHero.setResetModifier(
    [this](FlappyCatHero& hero) {
      hero.setRadius(mGameConstants.heroRadius());
      hero.moveTo(Position(-300.f, 0.f));
      hero.setColor(mGameConstants.colorScheme().hero());
    }
  );

  // initialize all stuff
  mFloor.initialize();
  mWalls.initialize();
  mBackgroundCity.initialize();
  mBackgroundSky.initialize();
  mHero.initialize();
}

void FlappyCatGame::reset() {

  mGameConstants.reset();

  mHero.reset();
  mWalls.reset();
  mFloor.reset();
  mBackgroundCity.reset();
  mBackgroundSky.reset();

}

void FlappyCatGame::processEvent(const Event& event) {

  if (event.type() == AndroidEvent::EventType::TouchEventType) {

    if (mGameState == PressButtonState) {

      mGameState = PlayState;

      // TODO: remove duplicate code and make jump function
      mHero.setAcceleration(Position(0.f, -800.f));
      mHero.setVelocity(Position(0.f, 800.f));
    }
    else if (mGameState == LoseState) {

      if (mHero.position().y() < -2000.f) {

        mGameState = PressButtonState;
        reset();
      }
    }
    else if (mGameState == PlayState) {

      using FloatSecond = std::chrono::duration<Position::value_type, std::ratio<1, 1>>;

      // hardcoded magic numbers
      mHero.setAcceleration(Position(0.f, -800.f));
      mHero.setVelocity(Position(0.f, 800.f));

      // TODO: do some physics
//    mHero.setAcceleration(Position(0.f, 0.f));
//
//    Position::value_type distance = (2.f * mHero.radius());
//
//    Position::value_type velocityY = distance / FloatSecond(1).count();
//
//    mHero.setVelocity(Position(0.f, velocityY));
    }
  }
}

void FlappyCatGame::update(const FrameDuration& time) {

  if (mGameState == PlayState) {

    mHero.update(time);
    mWalls.update(time);
    mFloor.update(time);
    mBackgroundCity.update(time);
  }
  else if (mGameState == LoseState) {

    mHero.update(time);
  }
  else if (mGameState == PressButtonState) {

    mFloor.update(time);
    mBackgroundCity.update(time);
  }
}

void FlappyCatGame::render(const Window& window) const {

  window.clear(mGameConstants.colorScheme().background());

  mBackgroundSky.drawOn(window);
  mBackgroundCity.drawOn(window);
  mFloor.drawOn(window);
  mWalls.drawOn(window);
  mHero.drawOn(window);

  window.display();
}
