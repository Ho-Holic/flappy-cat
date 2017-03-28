// self
#include "FlappyCatGame.h"
#include "FlappyCatClock.h"

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

  mFloor.setResetModifier(
    [this](FlappyCatFloor& floor) {
      mFloor.setMovementDisplacement(mGameConstants.foregroundDisplacement());
      floor.setColor(mGameConstants.colorScheme().block(),
                     mGameConstants.colorScheme().dirt());
    }
  );

  mFloor.setUpdateModifier(
    [this](FlappyCatFloor& floor, const FrameDuration& frameDuration) {

      Position::value_type radius = mHero.radius();
      // TODO: implement proper origin in 'transformation' and remove this code
      // circle origin in bottom left so we shift by radius
      Position center = mHero.position() + Position(radius, radius);

      if (mGameState == PlayState || mGameState == LoseState) {

        if (Collide::circleRect(center, radius, mFloor.boundingBox())) {
          mGameState = OnTheFloorState;
          Log::i(TAG, "Collide");
        }
      }
    }
  );

  // moving blocks
  mWalls.moveTo(Position(-mPlateWidth, -775.f));
  mWalls.resize(Position(mPlateWidth * 2.f, 0.f));
  mWalls.setStartOffset(Position(mPlateWidth * 4.f, 0.f));
  mWalls.setLinkSize(mGameConstants.wallSize());
  mWalls.setOffsetBetweenLinks(mGameConstants.wallSize() * 2.2f);
  mWalls.setMovementDisplacement(mGameConstants.foregroundDisplacement());

  mWalls.setResetModifier(
    [this](FlappyCatWall& wall) {
      wall.setGapInterval(mHero.radius() * 2.f * 4.f);

      wall.setGapDisplacement(mGameConstants.clampedRandomOffsetFrom(
        0.f, 200.f,
        FlappyCatGameConstants::Sign::Both)
      );

      wall.setColor(mGameConstants.colorScheme().block());
    }
  );

  mWalls.setUpdateModifier(
    [this](FlappyCatWall& wall) {

      Position::value_type radius = mHero.radius();
      // TODO: implement proper origin in 'transformation' and remove this code
      // circle origin in bottom left so we shift by radius
      Position center = mHero.position() + Position(radius, radius);

      if (mGameState == PlayState) {

        if (wall.collideWithCircle(center, radius)) {
          mGameState = LoseState;
          mFloor.setMovementDisplacement(Position(0.f, 0.f));
          Log::i(TAG, "Collide");
        }
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
  mBackgroundCity.setMovementDisplacement(mGameConstants.backgroundDisplacement());

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
    else if (mGameState == OnTheFloorState) {

        mGameState = PressButtonState;
        reset();
    }
    else if (mGameState == PlayState) {

      // don't jump out from screen
      if (mHero.position().y() < 800.f) {

        // hardcoded magic numbers
        mHero.setAcceleration(Position(0.f, -800.f));
        mHero.setVelocity(Position(0.f, 800.f));
      }
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
    mFloor.update(time);
  }
  else if (mGameState == OnTheFloorState) {
    // nothing to do here now
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

  mWalls.drawOn(window);
  mHero.drawOn(window);
  mFloor.drawOn(window);

  window.display();
}
