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
    m_acceleration = vec2(0.f, 0.f);
    m_velocity = vec2(0.f, 0.f);
    m_distance = vec2(0.f, 0.f);
}

void PhysicsBody::update(float time)
{
    // TODO: make list of physical forces instead of gravity variable
    m_acceleration = m_acceleration - m_gravity;
    m_velocity = m_velocity + (m_acceleration * time);

    m_distance = m_velocity * time; // distance passed by last update
}

const vec2& PhysicsBody::acceleration() const
{
    return m_acceleration;
}

const vec2& PhysicsBody::velocity() const
{
    return m_velocity;
}

const vec2& PhysicsBody::distance() const
{
    return m_distance;
}

void PhysicsBody::setAcceleration(const vec2& acceleration)
{
    m_acceleration = acceleration;
}

void PhysicsBody::setVelocity(const vec2& velocity)
{
    m_velocity = velocity;
}

void PhysicsBody::setGravity(const vec2& gravity)
{
    m_gravity = gravity;
}
