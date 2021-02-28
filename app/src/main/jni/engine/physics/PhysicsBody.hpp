#pragma once

#include <core/Position.hpp>

class PhysicsBody {
public:
    PhysicsBody();
    void reset();
    void update(float time);

public:
    const Position& acceleration() const;
    const Position& velocity() const;
    const Position& distance() const;
    void setAcceleration(const Position& acceleration);
    void setVelocity(const Position& velocity);
    void setGravity(const Position& gravity);

private:
    Position mGravity;
    Position m_acceleration;
    Position mVelocity;
    Position m_distance;
};
