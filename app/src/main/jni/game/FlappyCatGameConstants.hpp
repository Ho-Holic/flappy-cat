#pragma once

// game
#include "FlappyCatColorScheme.hpp"

// engine
#include <math/vec2.hpp>

// stl
#include <random>

enum class Daytime {
    Day,
    Night
};

class FlappyCatGameConstants {
public:
    enum Constants : size_t;

public:
    FlappyCatGameConstants();

public:
    void reset();

    // If you have error 'Error: 'FlappyCatColorScheme' does not name a type'
    // Then Android Studio accidentally insert following line
    //
    //     #include "FlappyCatGameConstants.hpp"
    //
    // to 'FlappyCatColorScheme.h'. Android studio really wants this line there
    // and don't want to deal with forward declarations of modern enums =)
    const FlappyCatColorScheme& colorScheme() const;

    vec2 operator[](Constants index) const;

public:
    float randomOffsetFrom(float initial,
        float maxOffset);

    float clampedRandomOffsetFrom(float initial,
        float maxOffset);

private:
    Daytime chooseDaytime();

private:
    std::random_device m_randomDevice;
    std::mt19937 m_generator;
    FlappyCatColorScheme m_colorScheme;
    std::vector<vec2> m_constants;
    int32_t m_daytimeFactor;
};

enum FlappyCatGameConstants::Constants : size_t {

    CameraSize,

    BarricadePosition,
    BarricadeSize,
    BarricadeWallSize,
    BarricadeBetweenWallOffset,
    BarricadeWallGapDisplacement,
    BarricadeStartOffset,

    CityPosition,
    CitySize,
    CityHouseSize,
    CityHouseOffset,

    FloorPosition,
    FloorSize,
    FloorOrganicSurfaceSize,
    FloorSpikesSize,

    HeroPosition,
    HeroSize,

    SkyCloudSize,
    SkyCloudOffset,
    SkyOffset,
    SkyCloudParts,

    PhysicsGravity,
    PhysicsBackgroundDisplacement,
    PhysicsForegroundDisplacement,
    PhysicsJumpAcceleration,
    PhysicsJumpVelocity,

    ConstantsSize
};
