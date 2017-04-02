// self
#include "FlappyCatGame.h"
#include "FlappyCatClock.h"

// engine
#include <core/Log.h>
#include <physics/Collide.h>


FlappyCatGame::FlappyCatGame()
: mGameConstants()
, mGameState(PressButtonState)
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

  // floor
  mFloor.moveTo(mGameConstants.floorPosition());
  mFloor.resize(mGameConstants.floorSize());

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
      // TODO: implement proper origin in 'transformation' and remove this line
      // circle origin in bottom left so we shift by radius
      Position center = mHero.position() + Position(radius, radius);

      if (mGameState == PlayState || mGameState == LoseState) {

        if (Collide::circleRect(center, radius, mFloor.boundingBox())) {
          mGameState = OnTheFloorState;
          mHero.moveTo(Position(mHero.position().x(), mFloor.position().y()));
        }
      }
    }
  );

  // moving blocks
  mWalls.moveTo(mGameConstants.barricadePosition());
  mWalls.resize(mGameConstants.barricadeSize());
  mWalls.setStartOffset(Position(mGameConstants.barricadeSize().x() * 2.f, 0.f));
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
  mBackgroundCity.moveTo(mGameConstants.cityPosition());
  mBackgroundCity.resize(mGameConstants.citySize());
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
  mBackgroundSky.setParts(100.f);
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

  // cat hero!
  mHero.setJumpConstants(Position(0.f, -800.f), Position(0.f, 800.f)); // hardcoded magic numbers

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
      mHero.jump();
    }
    else if (mGameState == OnTheFloorState) {

        mGameState = PressButtonState;
        reset();
    }
    else if (mGameState == PlayState) {

      // don't jump out of screen
      if (mHero.position().y() < ((cameraSize().y() / 2.f) - mGameConstants.heroRadius() * 4.f)) {

        mHero.jump();
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
