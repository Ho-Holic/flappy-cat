#include "PhysicsBody.hpp"

PhysicsBody::PhysicsBody()
    : mGravity(0.f, 0.f)
    , m_acceleration()
    , mVelocity()
    , mDistance()
{
    //
}

void PhysicsBody::reset()
{
    m_acceleration = Position(0.f, 0.f);
    mVelocity = Position(0.f, 0.f);
    mDistance = Position(0.f, 0.f);
}

void PhysicsBody::update(float time)
{
    // TODO: make list of physical forces instead of gravity variable
    m_acceleration = m_acceleration - mGravity;
    mVelocity = mVelocity + (m_acceleration * time);

    mDistance = mVelocity * time; // distance passed by last update
}

const Position& PhysicsBody::acceleration() const
{
    return m_acceleration;
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
    m_acceleration = acceleration;
}

void PhysicsBody::setVelocity(const Position& velocity)
{
    mVelocity = velocity;
}

void PhysicsBody::setGravity(const Position& gravity)
{
    mGravity = gravity;
}
