#include "FlappyCatGame.hpp"
#include "FlappyCatClock.hpp"
#include <core/Log.hpp>
#include <physics/Collide.hpp>
#include <physics/VectorMath.hpp>
#include <string>

FlappyCatGame::FlappyCatGame()
    : mGameConstants()
    , mGameState(PressButtonState)
    , m_background(mGameConstants)
    , m_floor(mGameConstants)
    , m_barricade(mGameConstants)
    , m_backgroundCity(mGameConstants)
    , m_backgroundSky(mGameConstants)
    , mHero(mGameConstants)
    , mLimit(mGameConstants)
    , mScore(mGameConstants)
    , mScoreCounter(0)
    , m_fps(mGameConstants)
    , m_fpsCounter(0)
{
    initialize();
    reset();
}

Position FlappyCatGame::cameraSize() const
{
    using Constant = FlappyCatGameConstants::Constants;

    return mGameConstants[Constant::CameraSize];
}

void FlappyCatGame::initialize()
{
    using Constant = FlappyCatGameConstants::Constants;
    using ColorConstant = FlappyCatColorScheme::Colors;

    // background
    m_background.moveTo(-(mGameConstants[Constant::CameraSize] / 2.f));
    m_background.resize(mGameConstants[Constant::CameraSize]);
    m_background.setResetModifier(
        [this](FlappyCatBackground& background) {
            const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

            background.setColor(colorScheme[ColorConstant::BackgroundColor]);
        });

    // limit
    mLimit.moveTo(-(mGameConstants[Constant::CameraSize] / 2.f));
    mLimit.resize(mGameConstants[Constant::CameraSize]);

    // floor
    m_floor.moveTo(mGameConstants[Constant::FloorPosition]);
    m_floor.resize(mGameConstants[Constant::FloorSize]);
    m_floor.setDecorationSizes(mGameConstants[Constant::FloorOrganicSurfaceSize],
        mGameConstants[Constant::FloorSpikesSize]);

    m_floor.setResetModifier(
        [this](FlappyCatFloor& floor) {
            const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

            floor.setMovementDisplacement(mGameConstants[Constant::PhysicsForegroundDisplacement]);
            floor.setColor(colorScheme[ColorConstant::BlockColor], colorScheme[ColorConstant::DirtColor]);
        });

    m_floor.setUpdateModifier(
        [this](FlappyCatFloor& floor, const FrameDuration&) {
            float radius = mHero.radius();
            // TODO: implement proper origin in 'transformation' and remove this line
            // circle origin in bottom left so we shift by radius
            Position center = mHero.position() + Position(radius, radius);

            if (mGameState == PlayState || mGameState == LoseState) {

                if (Collide::circleRect(center, radius, m_floor.boundingBox())) {
                    mGameState = OnTheFloorState;
                    mHero.moveTo(Position(mHero.position().x(), m_floor.position().y()));
                }
            }
        });

    // moving walls
    m_barricade.moveTo(mGameConstants[Constant::BarricadePosition]);
    m_barricade.resize(mGameConstants[Constant::BarricadeSize]);
    m_barricade.setStartOffset(mGameConstants[Constant::BarricadeStartOffset]);
    m_barricade.setLinkSize(mGameConstants[Constant::BarricadeWallSize]);
    m_barricade.setOffsetBetweenLinks(mGameConstants[Constant::BarricadeBetweenWallOffset]);
    m_barricade.setMovementDisplacement(mGameConstants[Constant::PhysicsForegroundDisplacement]);

    m_barricade.setResetModifier([this](FlappyCatChain<FlappyCatWall>& barricade) {
        barricade.foreachLink([this](FlappyCatWall& wall) {
            // reset
            wall.setResetModifier([this](FlappyCatWall& wall) {
                const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

                wall.setGapInterval(mHero.radius() * 2.f * 4.f);

                Position offset = mGameConstants[Constant::BarricadeWallGapDisplacement];
                wall.setGapDisplacement(mGameConstants.clampedRandomOffsetFrom(offset.x(), offset.y()));

                wall.setColor(colorScheme[ColorConstant::BlockColor]);
            });

            // update
            wall.setUpdateModifier([this](FlappyCatWall& wall, const FrameDuration&) {
                float radius = mHero.radius();
                // TODO: implement proper origin in 'transformation' and remove this code
                // circle origin in bottom left so we shift by radius
                Position center = mHero.position() + Position(radius, radius);

                if (mGameState == PlayState) {

                    if (wall.collideWithCircle(center, radius)) {

                        mGameState = LoseState;
                        m_floor.setMovementDisplacement(Position(0.f, 0.f));
                    } else if (!wall.isActivated() && wall.collideWithCircle(center, radius + radius * 0.2f)) {

                        wall.activateWall();
                        const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();
                        wall.setColor(colorScheme[ColorConstant::HeroColor]);
                    }
                }
            });
        });
    });

    m_barricade.setWrapAroundModifier(
        [this](FlappyCatWall& wall) {
            Position offset = mGameConstants[Constant::BarricadeWallGapDisplacement];
            wall.setGapDisplacement(mGameConstants.clampedRandomOffsetFrom(offset.x(), offset.y()));
        });

    // city buildings
    m_backgroundCity.moveTo(mGameConstants[Constant::CityPosition]);
    m_backgroundCity.resize(mGameConstants[Constant::CitySize]);
    m_backgroundCity.setLinkSize(mGameConstants[Constant::CityHouseSize]);
    m_backgroundCity.setMovementDisplacement(mGameConstants[Constant::PhysicsBackgroundDisplacement]);

    m_backgroundCity.setResetModifier([this](FlappyCatChain<FlappyCatSpike>& backgroundCity) {
        backgroundCity.foreachLink(
            [this](FlappyCatSpike& house) {
                house.setResetModifier([this](FlappyCatSpike& house) {
                    const FlappyCatColorScheme& colorScheme = mGameConstants.colorScheme();

                    Position offset = mGameConstants[Constant::CityHouseOffset];
                    Position varyingSize(mGameConstants[Constant::CityHouseSize]
                        + Position(0.f, std::abs(mGameConstants.randomOffsetFrom(offset.x(), offset.y()))));
                    house.resize(varyingSize);
                    house.setColor(colorScheme[ColorConstant::HouseColor]);
                });
            });
    });

    m_backgroundCity.setWrapAroundModifier(
        [this](FlappyCatSpike& house) {
            // add some variation to city buildings height
            Position offset = mGameConstants[Constant::CityHouseOffset];
            Position varyingSize(mGameConstants[Constant::CityHouseSize]
                + Position(0.f, std::abs(mGameConstants.randomOffsetFrom(offset.x(), offset.y()))));
            house.resize(varyingSize);
        });

    // sky with clouds
    m_backgroundSky.setParts(mGameConstants[Constant::SkyCloudParts].x());
    m_backgroundSky.setResetModifier(
        [this](FlappyCatCloud& sky) {
            sky.foreachCloud([this](CircleShape& cloud) {
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
            });
        });

    // cat hero!
    mHero.setJumpConstants(mGameConstants[Constant::PhysicsJumpAcceleration],
        mGameConstants[Constant::PhysicsJumpVelocity]);
    mHero.setGravity(mGameConstants[Constant::PhysicsGravity]);

    mHero.setUpdateModifier(
        [this](FlappyCatHero& hero, const FrameDuration&) {
            hero.moveBy(hero.distance());

            // tilt the hero
            float angle = hero.rotation();

            if (hero.distance().y() > 0.f) {
                if (angle < 35.f) {
                    angle += 2.5f;
                }
            } else {
                if (angle > -90.f) {
                    angle -= 2.5f;
                }
            }

            hero.rotateTo(angle);

            float offset = mGameConstants[Constant::HeroSize].x();
            mScore.moveTo(mHero.position() - Position(offset, offset / 4.f));
        });

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
        });

    // score counter
    mScore.setText("0");

    // fps counter
    m_fps.setText("0");

    // initialize all stuff
    m_background.initialize();
    m_floor.initialize();
    m_barricade.initialize();
    m_backgroundCity.initialize();
    m_backgroundSky.initialize();
    mHero.initialize();
    mLimit.initialize();
    mScore.initialize();
    m_fps.initialize();
}

void FlappyCatGame::reset()
{

    mGameConstants.reset();

    m_background.reset();
    mHero.reset();
    m_barricade.reset();
    m_floor.reset();
    m_backgroundCity.reset();
    m_backgroundSky.reset();
    mLimit.reset();
    resetScore();
}

void FlappyCatGame::processEvent(const Event& event)
{

    if (event.type() == Event::EventType::TouchEventType) {

        if (mGameState == PressButtonState) {

            mGameState = PlayState;
            mHero.jump();
            incrementScore();
        } else if (mGameState == OnTheFloorState) {

            mGameState = PressButtonState;
            reset();
        } else if (mGameState == PlayState) {

            bool isOffScreen = (mHero.position().y() < ((cameraSize().y() / 2.f) - mHero.radius() * 4.f));

            if (isOffScreen) {
                mHero.jump();
                incrementScore();
            }
        }
    }
}

void FlappyCatGame::update(const FrameDuration& time)
{

    if (mGameState == PlayState) {

        mHero.update(time);
        m_barricade.update(time);
        m_floor.update(time);
        m_backgroundCity.update(time);
    } else if (mGameState == LoseState) {

        mHero.update(time);
        m_floor.update(time);
    } else if (mGameState == OnTheFloorState) {
        // nothing to do here now
    } else if (mGameState == PressButtonState) {

        m_floor.update(time);
        m_backgroundCity.update(time);
    }

    m_fps.setText(std::to_string(m_fpsCounter));
}

void FlappyCatGame::render(const Window& window) const
{

    window.clear(Color(0, 0, 0));

    m_background.drawOn(window);

    m_backgroundSky.drawOn(window);
    m_backgroundCity.drawOn(window);

    m_barricade.drawOn(window);
    mHero.drawOn(window);
    m_floor.drawOn(window);
    mLimit.drawOn(window);
    mScore.drawOn(window);
    m_fps.drawOn(window);

    window.display();
}

void FlappyCatGame::incrementScore()
{
    mScoreCounter += 1;
    mScore.setText(std::to_string(mScoreCounter));
}

void FlappyCatGame::resetScore()
{
    mScoreCounter = 0;
    mScore.setText(std::to_string(mScoreCounter));

    using Constant = FlappyCatGameConstants::Constants;
    float offset = mGameConstants[Constant::HeroSize].x();
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
    m_fps.setColor(colorScheme[ColorConstant::TextColor]);
    m_fps.moveTo(mGameConstants[Constant::CameraSize] * 0.2f);
}

void FlappyCatGame::setFpsCounter(size_t fpsCount)
{
    m_fpsCounter = fpsCount;
}
