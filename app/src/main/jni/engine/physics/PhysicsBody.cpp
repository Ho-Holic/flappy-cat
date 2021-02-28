#include "PhysicsBody.hpp"

PhysicsBody::PhysicsBody()
    : m_gravity(0.f, 0.f)
    , m_acceleration()
    , m_velocity()
    , m_distance()
{
    //
}

void PhysicsBody::reset()
{
    m_acceleration = Position(0.f, 0.f);
    m_velocity = Position(0.f, 0.f);
    m_distance = Position(0.f, 0.f);
}

void PhysicsBody::update(float time)
{
    // TODO: make list of physical forces instead of gravity variable
    m_acceleration = m_acceleration - m_gravity;
    m_velocity = m_velocity + (m_acceleration * time);

    m_distance = m_velocity * time; // distance passed by last update
}

const Position& PhysicsBody::acceleration() const
{
    return m_acceleration;
}

const Position& PhysicsBody::velocity() const
{
    return m_velocity;
}

const Position& PhysicsBody::distance() const
{
    return m_distance;
}

void PhysicsBody::setAcceleration(const Position& acceleration)
{
    m_acceleration = acceleration;
}

void PhysicsBody::setVelocity(const Position& velocity)
{
    m_velocity = velocity;
}

void PhysicsBody::setGravity(const Position& gravity)
{
    m_gravity = gravity;
}
