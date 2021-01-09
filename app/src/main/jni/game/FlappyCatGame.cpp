// game
#include "FlappyCatGame.h"
#include "FlappyCatClock.h"

// engine
#include <core/Log.h>
#include <physics/Collide.h>
#include <physics/VectorMath.h>

// stl
#include <string>

FlappyCatGame::FlappyCatGame()
: mGameConstants()
, mGameState(PressButtonState)
, mScene()
, mBackground(mGameConstants)
, mFloor(mGameConstants)
, mBarricade(mGameConstants)
, mBackgroundCity(mGameConstants)
, mBackgroundSky(mGameConstants)
, mHero(mGameConstants)
, mLimit(mGameConstants)
, mScore(mGameConstants)
, mScoreCounter(0)
, mFps(mGameConstants)
, mFpsCounter(0) {
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

  // new code : testing
  //mScene.addChild();


  // background
  mBackground.moveTo(-(mGameConstants[Constant::CameraSize] / 2.f));
  mBackground.resize(mGameConstants[Constant::CameraSize]);
  mBackground.setResetModifier(
    [this](FlappyCatBackground& background) {

      const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

      background.setColor(colorScheme[ColorConstant::BackgroundColor]);
    }
  );

  // limit
  mLimit.moveTo(-(mGameConstants[Constant::CameraSize] / 2.f));
  mLimit.resize(mGameConstants[Constant::CameraSize]);

  // floor
  mFloor.moveTo(mGameConstants[Constant::FloorPosition]);
  mFloor.resize(mGameConstants[Constant::FloorSize]);
  mFloor.setDecorationSizes(mGameConstants[Constant::FloorOrganicSurfaceSize],
                            mGameConstants[Constant::FloorSpikesSize]);

  mFloor.setResetModifier(
    [this](FlappyCatFloor& floor) {

      const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

      floor.setMovementDisplacement(mGameConstants[Constant::PhysicsForegroundDisplacement]);
      floor.setColor(colorScheme[ColorConstant::BlockColor], colorScheme[ColorConstant::DirtColor]);
    }
  );

  mFloor.setUpdateModifier(
    [this](FlappyCatFloor& floor, const FrameDuration& frameDuration) {

      f32 radius = mHero.radius();
      // TODO: implement proper origin in 'transformation' and remove this line
      // circle origin in bottom left so we shift by radius
      Position center = mHero.position() + Position(radius, radius);

      if (mGameState == PlayState || mGameState == LoseState) {

        if (Collide::circleRect(center, radius, mFloor.boundingBox())) {
          mGameState = OnTheFloorState;
          mHero.moveTo(Position(mHero.position().x(), mFloor.position().y()));
        }
      }

      UNUSED(floor); // this update function process 'mHere' as a real target, not floor
      UNUSED(frameDuration); // not need for time processing here
    }
  );

  // moving walls
  mBarricade.moveTo(mGameConstants[Constant::BarricadePosition]);
  mBarricade.resize(mGameConstants[Constant::BarricadeSize]);
  mBarricade.setStartOffset(mGameConstants[Constant::BarricadeStartOffset]);
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

      f32 radius = mHero.radius();
      // TODO: implement proper origin in 'transformation' and remove this code
      // circle origin in bottom left so we shift by radius
      Position center = mHero.position() + Position(radius, radius);

      if (mGameState == PlayState) {

        if (wall.collideWithCircle(center, radius)) {

          mGameState = LoseState;
          mFloor.setMovementDisplacement(Position(0.f, 0.f));
          mHero.kill();
        }
        else if (wall.collideWithCircle(center, radius + 10.f)) {
          wall.activateWall();

          const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

          /*
           * TODO: remove extra color changes after collision
           *
           * On collision occures there is more then one collision
           * and you have grater color change
           *
           */
          uint8_t wallAlpha = wall.color().alpha() - static_cast<uint8_t>(32);
          if (wallAlpha <= 8) {
            wallAlpha = 8;
          }

          Color newColor(colorScheme[ColorConstant::HeroColor].r(),
                         colorScheme[ColorConstant::HeroColor].g(),
                         colorScheme[ColorConstant::HeroColor].b(),
                         wallAlpha);
          wall.setColor(newColor);
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
  mHero.setGravity(mGameConstants[Constant::PhysicsGravity]);

  mHero.setUpdateModifier(
    [this](FlappyCatHero& hero, const FrameDuration& frameDuration) {

      hero.moveBy(hero.distance());

      // tilt the hero
      f32 angle = hero.rotation();

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

      hero.rotateTo(angle);

      f32 offset = mGameConstants[Constant::HeroSize].x();
      mScore.moveTo(mHero.position() - Position(offset, offset / 4.f));

      UNUSED(frameDuration); // not need for time processing here
    }
  );

  mHero.setResetModifier(
    [this](FlappyCatHero& hero) {

      const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

      hero.setRadius(mGameConstants[Constant::HeroSize].x());
      hero.moveTo(mGameConstants[Constant::HeroPosition]);
      hero.rotateTo(0.f);

      hero.setColor(colorScheme[ColorConstant::HeroColor],
                    colorScheme[ColorConstant::MascotBodyColor],
                    colorScheme[ColorConstant::MascotScarfColor],
                    colorScheme[ColorConstant::MascotMouthColor]);
    }
  );

  // score counter
  mScore.setText("0");

  // fps counter
  mFps.setText("0");

  // initialize all stuff
  mBackground.initialize();
  mFloor.initialize();
  mBarricade.initialize();
  mBackgroundCity.initialize();
  mBackgroundSky.initialize();
  mHero.initialize();
  mLimit.initialize();
  mScore.initialize();
  mFps.initialize();
}

void FlappyCatGame::reset() {

  mGameConstants.reset();

  mBackground.reset();
  mHero.reset();
  mBarricade.reset();
  mFloor.reset();
  mBackgroundCity.reset();
  mBackgroundSky.reset();
  mLimit.reset();
  resetScore();

}

void FlappyCatGame::processEvent(const Event& event) {

  if (event.type() == Event::EventType::TouchEventType) {

    if (mGameState == PressButtonState) {

      mGameState = PlayState;
      mHero.jump();
      incrementScore();
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
        incrementScore();
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

  mFps.setText(std::to_string(mFpsCounter));
}

void FlappyCatGame::render(const Window& window) const {

  window.clear(Color(0, 0, 0));

  mBackground.drawOn(window);

  mBackgroundSky.drawOn(window);
  mBackgroundCity.drawOn(window);

  mBarricade.drawOn(window);
  mHero.drawOn(window);
  mFloor.drawOn(window);
  mLimit.drawOn(window);
  mScore.drawOn(window);
  mFps.drawOn(window);

  window.display();
}

void FlappyCatGame::incrementScore() {
  mScoreCounter += 1;
  mScore.setText(std::to_string(mScoreCounter));
}

void FlappyCatGame::resetScore() {
  mScoreCounter = 0;
  mScore.setText(std::to_string(mScoreCounter));

  using Constant = FlappyCatGameConstants::Constants;
  f32 offset = mGameConstants[Constant::HeroSize].x();
  mScore.moveTo(mHero.position() - Position(offset, offset / 4.f));

  /*
   * TODO: create own reset modifier for Score element
   */
  const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();
  using ColorConstant = FlappyCatColorScheme::Colors;
  mScore.setColor(colorScheme[ColorConstant::TextColor]);

  /*
   * TODO: create own reset modifier for Fps element
   */
  mFps.setColor(colorScheme[ColorConstant::TextColor]);
  mFps.moveTo(mGameConstants[Constant::CameraSize] * 0.2f);
}

void FlappyCatGame::setFpsCounter(size_t fpsCount) {
  mFpsCounter = fpsCount;
}
