#include "FlappyCatEntity.hpp"
#include <core/Log.hpp>

FlappyCatEntity::FlappyCatEntity(const FlappyCatGameConstants& gameConstants)
    : mGameConstants(gameConstants)
    , mPosition()
    , mSize()
    , mAngle(0.f)
    , mGravity(0.f, 0.f)
    , mAcceleration()
    , mVelocity()
    , mDistance()
{
    //
}

FlappyCatEntity::~FlappyCatEntity() = default;

void FlappyCatEntity::initialize()
{
    // intentionally left blank
}

void FlappyCatEntity::reset()
{
    //mPosition = Position(0.f, 0.f);
    //mSize = Position(0.f, 0.f);
    mAcceleration = Position(0.f, 0.f);
    mVelocity = Position(0.f, 0.f);
    mDistance = Position(0.f, 0.f);
}

void FlappyCatEntity::moveBy(const Position& offset)
{
    moveTo(position() + offset);
}

void FlappyCatEntity::moveTo(const Position& position)
{
    mPosition = position;
    syncChildren();
}

void FlappyCatEntity::resize(const Position& size)
{
    mSize = size;
    syncChildren();
}

void FlappyCatEntity::syncChildren()
{
    // intentionally left blank
}

void FlappyCatEntity::rotateTo(float angle)
{
    mAngle = angle;
    syncChildren();
}

/**
 * TODO: Create new entity for objects with physics
 *
 * Move this to PhysicsEntity or some other fancy name
 * This would prevent from calculating physics on static objects
 * and other that don't use this params
 * Normally if you would implement 'update()' yourself, you can
 * omit call to this function, but if you don't provide default one
 * this code would be called
 */
void FlappyCatEntity::update(const FrameDuration& frameDuration)
{
    float time = std::chrono::duration_cast<GameSecond>(frameDuration).count();

    // TODO: make list of physical forces instead of gravity variable
    mAcceleration = mAcceleration - mGravity;
    mVelocity = mVelocity + (mAcceleration * time);

    mDistance = mVelocity * time; // distance passed by last update
}

const FlappyCatGameConstants& FlappyCatEntity::gameConstants() const
{
    return mGameConstants;
}

const Position& FlappyCatEntity::position() const
{
    return mPosition;
}

const Position& FlappyCatEntity::size() const
{
    return mSize;
}

float FlappyCatEntity::rotation() const
{
    return mAngle;
}

const Position& FlappyCatEntity::acceleration() const
{
    return mAcceleration;
}

const Position& FlappyCatEntity::velocity() const
{
    return mVelocity;
}

const Position& FlappyCatEntity::distance() const
{
    return mDistance;
}

void FlappyCatEntity::setAcceleration(const Position& acceleration)
{
    mAcceleration = acceleration;
}

void FlappyCatEntity::setVelocity(const Position& velocity)
{
    mVelocity = velocity;
}

void FlappyCatEntity::setGravity(const Position& gravity)
{
    mGravity = gravity;
}
