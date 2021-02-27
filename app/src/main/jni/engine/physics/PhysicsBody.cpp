#include "PhysicsBody.hpp"

PhysicsBody::PhysicsBody()
    : mGravity(0.f, 0.f)
    , mAcceleration()
    , mVelocity()
    , mDistance()
{
    //
}

void PhysicsBody::reset()
{
    mAcceleration = Position(0.f, 0.f);
    mVelocity = Position(0.f, 0.f);
    mDistance = Position(0.f, 0.f);
}

void PhysicsBody::update(float time)
{
    // TODO: make list of physical forces instead of gravity variable
    mAcceleration = mAcceleration - mGravity;
    mVelocity = mVelocity + (mAcceleration * time);

    mDistance = mVelocity * time; // distance passed by last update
}

const Position& PhysicsBody::acceleration() const
{
    return mAcceleration;
}

const Position& PhysicsBody::velocity() const
{
    return mVelocity;
}

const Position& PhysicsBody::distance() const
{
    return mDistance;
}

void PhysicsBody::setAcceleration(const Position& acceleration)
{
    mAcceleration = acceleration;
}

void PhysicsBody::setVelocity(const Position& velocity)
{
    mVelocity = velocity;
}

void PhysicsBody::setGravity(const Position& gravity)
{
    mGravity = gravity;
}
