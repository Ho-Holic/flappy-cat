#include "FlappyCatGameConstants.hpp"
#include <core/Log.hpp>
#include <style/Guidelines.hpp>

FlappyCatGameConstants::FlappyCatGameConstants()
    : m_randomDevice()
    , m_generator(m_randomDevice())
    , m_colorScheme()
    , m_constants(ConstantsSize, vec2())
    , m_daytimeFactor(0)
{
    //
    // TODO: Remove 'reset()' and 'm_daytimeFactor = 0'
    //
    // Call is not needed but directly we can't remove it
    // This would cause all objects to disappear
    // because 'initialize()' function uses 'm_constants'
    // Seems this is deep arch issue, figure out how to
    // improve the design
    //
    reset();
    m_daytimeFactor = 0;
}

Daytime FlappyCatGameConstants::chooseDaytime()
{
    // small code for day/night cycling

    enum {
        Period = 3
    };

    Daytime daytime = (m_daytimeFactor < Period) ? Daytime::Day
                                                 : Daytime::Night;

    m_daytimeFactor = (m_daytimeFactor + 1) % (Period * 2);

    return daytime;
}

vec2 FlappyCatGameConstants::operator[](FlappyCatGameConstants::Constants index) const
{
    REQUIRE(TAG, index < ConstantsSize, "m_constants out of bounds");
    return m_constants[index];
}

void FlappyCatGameConstants::reset()
{
    Daytime daytime = chooseDaytime();

    m_colorScheme.generateNewScheme(daytime);

    vec2 cameraSize = vec2(1080.f, 1920.f);

    float plateWidth = 1000.f;

    float halfCameraY = cameraSize.y / 2.f;
    float offsetFloorY = halfCameraY * 0.8f; // ground takes 20%

    // camera
    m_constants[CameraSize] = cameraSize;

    // floor
    m_constants[FloorPosition] = vec2(-plateWidth, -offsetFloorY);
    m_constants[FloorSize] = vec2(plateWidth * 2.f, halfCameraY - offsetFloorY);
    m_constants[FloorOrganicSurfaceSize] = vec2(0.f, 20.f);
    m_constants[FloorSpikesSize] = vec2(25.f, 25.f);

    // barricade
    m_constants[BarricadeWallSize] = vec2(180.f, halfCameraY + offsetFloorY);
    m_constants[BarricadeBetweenWallOffset] = 2.2f * vec2(180.f, 0.f);
    m_constants[BarricadePosition] = vec2(-plateWidth, -offsetFloorY);
    m_constants[BarricadeSize] = vec2(plateWidth * 2.f, halfCameraY + offsetFloorY);
    m_constants[BarricadeWallGapDisplacement] = vec2(0.f, 300.f);
    m_constants[BarricadeStartOffset] = vec2(plateWidth * 2.5f, 0.f);

    // city
    m_constants[CityHouseOffset] = vec2(0.f, 200.f);
    m_constants[CityHouseSize] = vec2(100.f, 150.f);
    m_constants[CityPosition] = vec2(-plateWidth, -offsetFloorY);
    m_constants[CitySize] = vec2(plateWidth * 2.f, 0.f);

    // hero
    m_constants[HeroPosition] = vec2(-300.f, 0.f);
    m_constants[HeroSize] = vec2(50.f, 50.f);

    // clouds
    // constants for 'daytime == Daytime::Day'
    m_constants[SkyCloudSize] = vec2(20.f, 20.f);
    m_constants[SkyCloudOffset] = vec2(0.f, 100.f);
    m_constants[SkyOffset] = vec2(0.f, 500.f);
    m_constants[SkyCloudParts] = vec2(100.f, 0.f);

    if (daytime == Daytime::Night) {
        m_constants[SkyCloudSize] = vec2(1.f, 0.f);
        m_constants[SkyCloudOffset] = vec2(0.f, 5.f);
        m_constants[SkyOffset] = vec2(0.f, 500.f);
        m_constants[SkyCloudParts] = vec2(50.f, 0.f);
    }

    // physics
    m_constants[PhysicsGravity] = vec2(0.f, 100.f);
    m_constants[PhysicsBackgroundDisplacement] = vec2(-2.8f, 0.f);
    m_constants[PhysicsForegroundDisplacement] = vec2(-7.f, 0.f);
    m_constants[PhysicsJumpAcceleration] = vec2(0.f, -800.f);
    m_constants[PhysicsJumpVelocity] = vec2(0.f, 800.f);
}

const FlappyCatColorScheme& FlappyCatGameConstants::colorScheme() const
{
    return m_colorScheme;
}

float FlappyCatGameConstants::randomOffsetFrom(float initial,
    float maxOffset)
{
    std::normal_distribution<float> distribution(initial, maxOffset);

    return distribution(m_generator);
}

float FlappyCatGameConstants::clampedRandomOffsetFrom(float initial,
    float maxOffset)
{
    return std::clamp(randomOffsetFrom(initial, maxOffset),
        initial - maxOffset,
        initial + maxOffset);
}
