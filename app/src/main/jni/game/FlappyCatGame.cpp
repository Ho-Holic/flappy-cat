#include "FlappyCatGame.hpp"
#include "FlappyCatClock.hpp"
#include <core/Log.hpp>
#include <physics/Collide.hpp>
#include <physics/VectorMath.hpp>
#include <string>

FlappyCatGame::FlappyCatGame()
    : m_gameConstants()
    , m_gameState(PressButtonState)
    , m_background(m_gameConstants)
    , m_floor(m_gameConstants)
    , m_barricade(m_gameConstants)
    , m_backgroundCity(m_gameConstants)
    , m_backgroundSky(m_gameConstants)
    , m_hero(m_gameConstants)
    , m_limit(m_gameConstants)
    , m_score(m_gameConstants)
    , m_scoreCounter(0)
    , m_fps(m_gameConstants)
    , m_fpsCounter(0)
{
    initialize();
    reset();
}

Position FlappyCatGame::cameraSize() const
{
    using Constant = FlappyCatGameConstants::Constants;

    return m_gameConstants[Constant::CameraSize];
}

void FlappyCatGame::initialize()
{
    using Constant = FlappyCatGameConstants::Constants;
    using ColorConstant = FlappyCatColorScheme::Colors;

    // background
    m_background.moveTo(-(m_gameConstants[Constant::CameraSize] / 2.f));
    m_background.resize(m_gameConstants[Constant::CameraSize]);
    m_background.setResetModifier(
        [this](FlappyCatBackground& background) {
            const FlappyCatColorScheme& colorScheme = m_gameConstants.colorScheme();

            background.setColor(colorScheme[ColorConstant::BackgroundColor]);
        });

    // limit
    m_limit.moveTo(-(m_gameConstants[Constant::CameraSize] / 2.f));
    m_limit.resize(m_gameConstants[Constant::CameraSize]);

    // floor
    m_floor.moveTo(m_gameConstants[Constant::FloorPosition]);
    m_floor.resize(m_gameConstants[Constant::FloorSize]);
    m_floor.setDecorationSizes(m_gameConstants[Constant::FloorOrganicSurfaceSize],
        m_gameConstants[Constant::FloorSpikesSize]);

    m_floor.setResetModifier(
        [this](FlappyCatFloor& floor) {
            const FlappyCatColorScheme& colorScheme = m_gameConstants.colorScheme();

            floor.setMovementDisplacement(m_gameConstants[Constant::PhysicsForegroundDisplacement]);
            floor.setColor(colorScheme[ColorConstant::BlockColor], colorScheme[ColorConstant::DirtColor]);
        });

    m_floor.setUpdateModifier(
        [this](FlappyCatFloor& floor, const FrameDuration&) {
            float radius = m_hero.radius();
            // TODO: implement proper origin in 'transformation' and remove this line
            // circle origin in bottom left so we shift by radius
            Position center = m_hero.position() + Position(radius, radius);

            if (m_gameState == PlayState || m_gameState == LoseState) {

                if (Collide::circleRect(center, radius, m_floor.boundingBox())) {
                    m_gameState = OnTheFloorState;
                    m_hero.moveTo(Position(m_hero.position().x(), m_floor.position().y()));
                }
            }
        });

    // moving walls
    m_barricade.moveTo(m_gameConstants[Constant::BarricadePosition]);
    m_barricade.resize(m_gameConstants[Constant::BarricadeSize]);
    m_barricade.setStartOffset(m_gameConstants[Constant::BarricadeStartOffset]);
    m_barricade.setLinkSize(m_gameConstants[Constant::BarricadeWallSize]);
    m_barricade.setOffsetBetweenLinks(m_gameConstants[Constant::BarricadeBetweenWallOffset]);
    m_barricade.setMovementDisplacement(m_gameConstants[Constant::PhysicsForegroundDisplacement]);

    m_barricade.setResetModifier([this](FlappyCatChain<FlappyCatWall>& barricade) {
        barricade.foreachLink([this](FlappyCatWall& wall) {
            // reset
            wall.setResetModifier([this](FlappyCatWall& wall) {
                const FlappyCatColorScheme& colorScheme = m_gameConstants.colorScheme();

                wall.setGapInterval(m_hero.radius() * 2.f * 4.f);

                Position offset = m_gameConstants[Constant::BarricadeWallGapDisplacement];
                wall.setGapDisplacement(m_gameConstants.clampedRandomOffsetFrom(offset.x(), offset.y()));

                wall.setColor(colorScheme[ColorConstant::BlockColor]);
            });

            // update
            wall.setUpdateModifier([this](FlappyCatWall& wall, const FrameDuration&) {
                float radius = m_hero.radius();
                // TODO: implement proper origin in 'transformation' and remove this code
                // circle origin in bottom left so we shift by radius
                Position center = m_hero.position() + Position(radius, radius);

                if (m_gameState == PlayState) {

                    if (wall.collideWithCircle(center, radius)) {

                        m_gameState = LoseState;
                        m_floor.setMovementDisplacement(Position(0.f, 0.f));
                    } else if (!wall.isActivated() && wall.collideWithCircle(center, radius + radius * 0.2f)) {

                        wall.activateWall();
                        const FlappyCatColorScheme& colorScheme = m_gameConstants.colorScheme();
                        wall.setColor(colorScheme[ColorConstant::HeroColor]);
                    }
                }
            });
        });
    });

    m_barricade.setWrapAroundModifier(
        [this](FlappyCatWall& wall) {
            Position offset = m_gameConstants[Constant::BarricadeWallGapDisplacement];
            wall.setGapDisplacement(m_gameConstants.clampedRandomOffsetFrom(offset.x(), offset.y()));
        });

    // city buildings
    m_backgroundCity.moveTo(m_gameConstants[Constant::CityPosition]);
    m_backgroundCity.resize(m_gameConstants[Constant::CitySize]);
    m_backgroundCity.setLinkSize(m_gameConstants[Constant::CityHouseSize]);
    m_backgroundCity.setMovementDisplacement(m_gameConstants[Constant::PhysicsBackgroundDisplacement]);

    m_backgroundCity.setResetModifier([this](FlappyCatChain<FlappyCatSpike>& backgroundCity) {
        backgroundCity.foreachLink(
            [this](FlappyCatSpike& house) {
                house.setResetModifier([this](FlappyCatSpike& house) {
                    const FlappyCatColorScheme& colorScheme = m_gameConstants.colorScheme();

                    Position offset = m_gameConstants[Constant::CityHouseOffset];
                    Position varyingSize(m_gameConstants[Constant::CityHouseSize]
                        + Position(0.f, std::abs(m_gameConstants.randomOffsetFrom(offset.x(), offset.y()))));
                    house.resize(varyingSize);
                    house.setColor(colorScheme[ColorConstant::HouseColor]);
                });
            });
    });

    m_backgroundCity.setWrapAroundModifier(
        [this](FlappyCatSpike& house) {
            // add some variation to city buildings height
            Position offset = m_gameConstants[Constant::CityHouseOffset];
            Position varyingSize(m_gameConstants[Constant::CityHouseSize]
                + Position(0.f, std::abs(m_gameConstants.randomOffsetFrom(offset.x(), offset.y()))));
            house.resize(varyingSize);
        });

    // sky with clouds
    m_backgroundSky.setParts(m_gameConstants[Constant::SkyCloudParts].x());
    m_backgroundSky.setResetModifier(
        [this](FlappyCatCloud& sky) {
            sky.foreachCloud([this](CircleShape& cloud) {
                const FlappyCatColorScheme& colorScheme = m_gameConstants.colorScheme();

                Position cloudOffset = m_gameConstants[Constant::SkyCloudOffset];
                Position skyOffset = m_gameConstants[Constant::SkyOffset];

                cloud.geometry().setRadius(m_gameConstants[Constant::SkyCloudSize].x()
                    + std::abs(m_gameConstants.randomOffsetFrom(cloudOffset.x(),
                        cloudOffset.y())));

                Position pos(m_gameConstants.randomOffsetFrom(skyOffset.x(), skyOffset.y()),
                    m_gameConstants.randomOffsetFrom(skyOffset.x(), skyOffset.y()));

                cloud.transformation().setPosition(pos);
                cloud.setColor(colorScheme[ColorConstant::CloudColor]);
            });
        });

    // cat hero!
    m_hero.setJumpConstants(m_gameConstants[Constant::PhysicsJumpAcceleration],
        m_gameConstants[Constant::PhysicsJumpVelocity]);
    m_hero.setGravity(m_gameConstants[Constant::PhysicsGravity]);

    m_hero.setUpdateModifier(
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

            float offset = m_gameConstants[Constant::HeroSize].x();
            m_score.moveTo(m_hero.position() - Position(offset, offset / 4.f));
        });

    m_hero.setResetModifier(
        [this](FlappyCatHero& hero) {
            const FlappyCatColorScheme& colorScheme = m_gameConstants.colorScheme();

            hero.setRadius(m_gameConstants[Constant::HeroSize].x());
            hero.moveTo(m_gameConstants[Constant::HeroPosition]);
            hero.rotateTo(0.f);

            hero.setColor(colorScheme[ColorConstant::HeroColor],
                colorScheme[ColorConstant::MascotBodyColor],
                colorScheme[ColorConstant::MascotScarfColor],
                colorScheme[ColorConstant::MascotMouthColor]);
        });

    // score counter
    m_score.setText("0");

    // fps counter
    m_fps.setText("0");

    // initialize all stuff
    m_background.initialize();
    m_floor.initialize();
    m_barricade.initialize();
    m_backgroundCity.initialize();
    m_backgroundSky.initialize();
    m_hero.initialize();
    m_limit.initialize();
    m_score.initialize();
    m_fps.initialize();
}

void FlappyCatGame::reset()
{

    m_gameConstants.reset();

    m_background.reset();
    m_hero.reset();
    m_barricade.reset();
    m_floor.reset();
    m_backgroundCity.reset();
    m_backgroundSky.reset();
    m_limit.reset();
    resetScore();
}

void FlappyCatGame::processEvent(const Event& event)
{

    if (event.type() == Event::EventType::TouchEventType) {

        if (m_gameState == PressButtonState) {

            m_gameState = PlayState;
            m_hero.jump();
            incrementScore();
        } else if (m_gameState == OnTheFloorState) {

            m_gameState = PressButtonState;
            reset();
        } else if (m_gameState == PlayState) {

            bool isOffScreen = (m_hero.position().y() < ((cameraSize().y() / 2.f) - m_hero.radius() * 4.f));

            if (isOffScreen) {
                m_hero.jump();
                incrementScore();
            }
        }
    }
}

void FlappyCatGame::update(const FrameDuration& time)
{

    if (m_gameState == PlayState) {

        m_hero.update(time);
        m_barricade.update(time);
        m_floor.update(time);
        m_backgroundCity.update(time);
    } else if (m_gameState == LoseState) {

        m_hero.update(time);
        m_floor.update(time);
    } else if (m_gameState == OnTheFloorState) {
        // nothing to do here now
    } else if (m_gameState == PressButtonState) {

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
    m_hero.drawOn(window);
    m_floor.drawOn(window);
    m_limit.drawOn(window);
    m_score.drawOn(window);
    m_fps.drawOn(window);

    window.display();
}

void FlappyCatGame::incrementScore()
{
    m_scoreCounter += 1;
    m_score.setText(std::to_string(m_scoreCounter));
}

void FlappyCatGame::resetScore()
{
    m_scoreCounter = 0;
    m_score.setText(std::to_string(m_scoreCounter));

    using Constant = FlappyCatGameConstants::Constants;
    float offset = m_gameConstants[Constant::HeroSize].x();
    m_score.moveTo(m_hero.position() - Position(offset, offset / 4.f));

    /*
   * TODO: create own reset modifier for Score element
   */
    const FlappyCatColorScheme& colorScheme = m_gameConstants.colorScheme();
    using ColorConstant = FlappyCatColorScheme::Colors;
    m_score.setColor(colorScheme[ColorConstant::TextColor]);

    /*
   * TODO: create own reset modifier for Fps element
   */
    m_fps.setColor(colorScheme[ColorConstant::TextColor]);
    m_fps.moveTo(m_gameConstants[Constant::CameraSize] * 0.2f);
}

void FlappyCatGame::setFpsCounter(size_t fpsCount)
{
    m_fpsCounter = fpsCount;
}
