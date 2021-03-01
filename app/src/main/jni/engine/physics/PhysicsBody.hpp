#pragma once

#include <math/vec2.hpp>

class PhysicsBody {
public:
    PhysicsBody();
    void reset();
    void update(float time);

public:
    const vec2& acceleration() const;
    const vec2& velocity() const;
    const vec2& distance() const;
    void setAcceleration(const vec2& acceleration);
    void setVelocity(const vec2& velocity);
    void setGravity(const vec2& gravity);

private:
    vec2 m_gravity;
    vec2 m_acceleration;
    vec2 m_velocity;
    vec2 m_distance;
};
