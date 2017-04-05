// game
#include "FlappyCatGame.h"
#include "FlappyCatClock.h"

// engine
#include <core/Log.h>
#include <physics/Collide.h>


FlappyCatGame::FlappyCatGame()
: mGameConstants()
, mGameState(PressButtonState)
, mFloor(mGameConstants)
, mBarricade(mGameConstants)
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

  // moving walls
  mBarricade.moveTo(mGameConstants.barricadePosition());
  mBarricade.resize(mGameConstants.barricadeSize());
  mBarricade.setStartOffset(Position(mGameConstants.barricadeSize().x() * 2.f, 0.f));
  mBarricade.setLinkSize(mGameConstants.wallSize());
  mBarricade.setOffsetBetweenLinks(mGameConstants.wallSize() * 2.2f);
  mBarricade.setMovementDisplacement(mGameConstants.foregroundDisplacement());

  mBarricade.setResetModifier(
    [this](FlappyCatWall& wall) {

      wall.setGapInterval(mHero.radius() * 2.f * 4.f);

      Position offset = mGameConstants.wallOffset();
      wall.setGapDisplacement(mGameConstants.clampedRandomOffsetFrom(offset.x(), offset.y()));

      wall.setColor(mGameConstants.colorScheme().block());
    }
  );

  mBarricade.setUpdateModifier(
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

  mBarricade.setWrapAroundModifier(
    [this](FlappyCatWall& wall) {

      Position offset = mGameConstants.wallOffset();
      wall.setGapDisplacement(mGameConstants.clampedRandomOffsetFrom(offset.x(), offset.y()));
    }
  );

  // city buildings
  mBackgroundCity.moveTo(mGameConstants.cityPosition());
  mBackgroundCity.resize(mGameConstants.citySize());
  mBackgroundCity.setLinkSize(mGameConstants.houseSize());
  mBackgroundCity.setMovementDisplacement(mGameConstants.backgroundDisplacement());

  mBackgroundCity.setResetModifier(
    [this](FlappyCatSpike& house) {

      Position offset = mGameConstants.houseOffset();
      Position varyingSize(mGameConstants.houseSize()
                           + Position(0.f, std::abs(mGameConstants.randomOffsetFrom(offset.x(),
                                                                                    offset.y()))));
      house.resize(varyingSize);
      house.setColor(mGameConstants.colorScheme().house());
    }
  );

  mBackgroundCity.setWrapAroundModifier(
    [this](FlappyCatSpike& house) {

      Position offset = mGameConstants.houseOffset();
      Position varyingSize(mGameConstants.houseSize()
                           + Position(0.f, std::abs(mGameConstants.randomOffsetFrom(offset.x(),
                                                                                    offset.y()))));
      house.resize(varyingSize);
    }
  );

  // sky with clouds
  mBackgroundSky.setParts(mGameConstants.cloudParts().x());
  mBackgroundSky.setResetModifier(
    [this](FlappyCatCloud::entity_type& cloud) {

      Position cloudOffset = mGameConstants.cloudOffset();
      Position skyOffset = mGameConstants.skyOffset();

      cloud.geometry().setRadius(mGameConstants.cloudSize().x()
                               + std::abs(mGameConstants.randomOffsetFrom(cloudOffset.x(),
                                                                          cloudOffset.y())));

      Position pos(mGameConstants.randomOffsetFrom(skyOffset.x(), skyOffset.y()),
                   mGameConstants.randomOffsetFrom(skyOffset.x(), skyOffset.y()));

      cloud.transformation().setPosition(pos);
      cloud.setColor(mGameConstants.colorScheme().cloud());
    }
  );

  // cat hero!
  mHero.setJumpConstants(mGameConstants.jumpAcceleration(),
                         mGameConstants.jumpVelocity());

  mHero.setUpdateModifier(
    [this](FlappyCatHero& hero, const FrameDuration& frameDuration) {

      hero.moveBy(hero.distance());
    }
  );

  mHero.setResetModifier(
    [this](FlappyCatHero& hero) {

      hero.setRadius(mGameConstants.heroSize().x());
      hero.moveTo(mGameConstants.heroPosition());

      hero.setColor(mGameConstants.colorScheme().hero(),
                    mGameConstants.colorScheme().mascotBody(),
                    mGameConstants.colorScheme().mascotScarf(),
                    mGameConstants.colorScheme().mascotMouth());
    }
  );

  // initialize all stuff
  mFloor.initialize();
  mBarricade.initialize();
  mBackgroundCity.initialize();
  mBackgroundSky.initialize();
  mHero.initialize();
}

void FlappyCatGame::reset() {

  mGameConstants.reset();

  mHero.reset();
  mBarricade.reset();
  mFloor.reset();
  mBackgroundCity.reset();
  mBackgroundSky.reset();

}

void FlappyCatGame::processEvent(const Event& event) {

  if (event.type() == Event::EventType::TouchEventType) {

    if (mGameState == PressButtonState) {

      mGameState = PlayState;
      mHero.jump();
    }
    else if (mGameState == OnTheFloorState) {

        mGameState = PressButtonState;
        reset();
    }
    else if (mGameState == PlayState) {

      bool isOffScreen = (
        mHero.position().y() < ((cameraSize().y() / 2.f) - mHero.radius() * 4.f)
      );

      if (isOffScreen) {
        mHero.jump();
      }
    }
  }
}

void FlappyCatGame::update(const FrameDuration& time) {

  if (mGameState == PlayState) {

    mHero.update(time);
    mBarricade.update(time);
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

  mBarricade.drawOn(window);
  mHero.drawOn(window);
  mFloor.drawOn(window);


  // TODO: remove code below
//  // --- tmp v
//  static float p = 0;
//
//  RectangleShape rect(Position(0.f, 0.f), Position(100.f, 100.f));
//  rect.transformation().setRotation(p);
//  rect.transformation().setOrigin(Position(200.f, 200.f));
//  window.draw(rect);
//
//  p += 0.1;
//
//  if (p > 360.f) p = 0.f;
//  // --- tmp ^



  window.display();
}
