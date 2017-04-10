// game
#include "FlappyCatGame.h"
#include "FlappyCatClock.h"

// engine
#include <core/Log.h>
#include <physics/Collide.h>
#include <physics/VectorMath.h>

// style
#include <style/BackportCpp17.h>


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

  using Constant = FlappyCatGameConstants::Constants;

  return mGameConstants[Constant::CameraSize];
}

void FlappyCatGame::initialize() {

  using Constant = FlappyCatGameConstants::Constants;
  using ColorConstant = FlappyCatColorScheme::Colors;

  // floor
  mFloor.moveTo(mGameConstants[Constant::FloorPosition]);
  mFloor.resize(mGameConstants[Constant::FloorSize]);
  mFloor.setDecorationSizes(mGameConstants[Constant::FloorOrganicSurfaceSize],
                            mGameConstants[Constant::FloorSpikesSize]);

  mFloor.setResetModifier(
    [this](FlappyCatFloor& floor) {

      const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

      mFloor.setMovementDisplacement(mGameConstants[Constant::PhysicsForegroundDisplacement]);
      floor.setColor(colorScheme[ColorConstant::BlockColor], colorScheme[ColorConstant::DirtColor]);
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
  mBarricade.moveTo(mGameConstants[Constant::BarricadePosition]);
  mBarricade.resize(mGameConstants[Constant::BarricadeSize]);
  mBarricade.setStartOffset(Position(mGameConstants[Constant::BarricadeSize].x() * 2.f, 0.f));
  mBarricade.setLinkSize(mGameConstants[Constant::BarricadeWallSize]);
  mBarricade.setOffsetBetweenLinks(mGameConstants[Constant::BarricadeBetweenWallOffset]);
  mBarricade.setMovementDisplacement(mGameConstants[Constant::PhysicsForegroundDisplacement]);

  mBarricade.setResetModifier(
    [this](FlappyCatWall& wall) {

      const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

      wall.setGapInterval(mHero.radius() * 2.f * 4.f);

      Position offset = mGameConstants[Constant::BarricadeWallGapDisplacement];
      wall.setGapDisplacement(mGameConstants.clampedRandomOffsetFrom(offset.x(), offset.y()));

      wall.setColor(colorScheme[ColorConstant::BlockColor]);
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

      Position offset = mGameConstants[Constant::BarricadeWallGapDisplacement];
      wall.setGapDisplacement(mGameConstants.clampedRandomOffsetFrom(offset.x(), offset.y()));
    }
  );

  // city buildings
  mBackgroundCity.moveTo(mGameConstants[Constant::CityPosition]);
  mBackgroundCity.resize(mGameConstants[Constant::CitySize]);
  mBackgroundCity.setLinkSize(mGameConstants[Constant::CityHouseSize]);
  mBackgroundCity.setMovementDisplacement(mGameConstants[Constant::PhysicsBackgroundDisplacement]);

  mBackgroundCity.setResetModifier(
    [this](FlappyCatSpike& house) {

      const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

      Position offset = mGameConstants[Constant::CityHouseOffset];
      Position varyingSize(mGameConstants[Constant::CityHouseSize]
                           + Position(0.f, std::abs(mGameConstants.randomOffsetFrom(offset.x(),
                                                                                    offset.y()))));
      house.resize(varyingSize);
      house.setColor(colorScheme[ColorConstant::HouseColor]);
    }
  );

  mBackgroundCity.setWrapAroundModifier(
    [this](FlappyCatSpike& house) {

      Position offset = mGameConstants[Constant::CityHouseOffset];
      Position varyingSize(mGameConstants[Constant::CityHouseSize]
                           + Position(0.f, std::abs(mGameConstants.randomOffsetFrom(offset.x(),
                                                                                    offset.y()))));
      house.resize(varyingSize);
    }
  );

  // sky with clouds
  mBackgroundSky.setParts(mGameConstants[Constant::SkyCloudParts].x());
  mBackgroundSky.setResetModifier(
    [this](FlappyCatCloud::entity_type& cloud) {

      const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

      Position cloudOffset = mGameConstants[Constant::SkyCloudOffset];
      Position skyOffset = mGameConstants[Constant::SkyOffset];

      cloud.geometry().setRadius(mGameConstants[Constant::SkyCloudSize].x()
                               + std::abs(mGameConstants.randomOffsetFrom(cloudOffset.x(),
                                                                          cloudOffset.y())));

      Position pos(mGameConstants.randomOffsetFrom(skyOffset.x(), skyOffset.y()),
                   mGameConstants.randomOffsetFrom(skyOffset.x(), skyOffset.y()));

      cloud.transformation().setPosition(pos);
      cloud.setColor(colorScheme[ColorConstant::CloudColor]);
    }
  );

  // cat hero!
  mHero.setJumpConstants(mGameConstants[Constant::PhysicsJumpAcceleration],
                         mGameConstants[Constant::PhysicsJumpVelocity]);

  mHero.setUpdateModifier(
    [this](FlappyCatHero& hero, const FrameDuration& frameDuration) {

      hero.moveBy(hero.distance());

      // tilt the hero
      Position::value_type angle = hero.rotation();

      if (hero.distance().y() > 0.f) {
        if (angle < 35.f) {
          angle += 2.5f;
        }
      }
      else {
        if (angle > -90.f) {
          angle -= 2.5f;
        }
      }

      hero.rotate(angle);
    }
  );

  mHero.setResetModifier(
    [this](FlappyCatHero& hero) {

      const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

      hero.setRadius(mGameConstants[Constant::HeroSize].x());
      hero.moveTo(mGameConstants[Constant::HeroPosition]);
      hero.rotate(0.f);

      hero.setColor(colorScheme[ColorConstant::HeroColor],
                    colorScheme[ColorConstant::MascotBodyColor],
                    colorScheme[ColorConstant::MascotScarfColor],
                    colorScheme[ColorConstant::MascotMouthColor]);
    }
  );

  // initialize all stuff
  Log::i(TAG, "Floor:");
  mFloor.initialize();
  Log::i(TAG, "Barricade:");
  mBarricade.initialize();
  Log::i(TAG, "City:");
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

  using ColorConstant = FlappyCatColorScheme::Colors;
  const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

  window.clear(colorScheme[ColorConstant::BackgroundColor]);

  mBackgroundSky.drawOn(window);
  mBackgroundCity.drawOn(window);

  mBarricade.drawOn(window);
  mHero.drawOn(window);
  mFloor.drawOn(window);

//  // tmp
//  FlappyCatSpike frame(mGameConstants);
//  frame.setColor(Color(255, 0, 0, 128));
//  frame.moveTo(-Position(cameraSize().x() / 2.f, cameraSize().y() / 2.f));
//  frame.resize(cameraSize());
//  frame.drawOn(window);
//  // end tmp

  window.display();
}
