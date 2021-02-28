#pragma once

#include <core/Window.hpp>
#include <game/FlappyCatClock.hpp>
#include <game/FlappyCatGameConstants.hpp>
#include <physics/PhysicsBody.hpp>

class FlappyCatEntity {
public:
    FlappyCatEntity(const FlappyCatGameConstants& gameConstants);
    virtual ~FlappyCatEntity();

public:
    virtual void initialize() = 0;
    virtual void reset() = 0;
    virtual void update(const FrameDuration& frameDuration) = 0;
    virtual void drawOn(const Window& window) const = 0;

    virtual const Position& position() const;
    virtual float rotation() const;
    virtual const Position& size() const;

    virtual void moveTo(const Position& position);
    virtual void moveBy(const Position& offset);

    virtual void resize(const Position& size);
    virtual void rotateTo(float angle);

public:
    const FlappyCatGameConstants& gameConstants() const;

private:
    virtual void syncChildren();

private:
    const FlappyCatGameConstants& m_gameConstants;
    Position m_position;
    Position mSize;
    float m_angle;
    PhysicsBody m_body;
};
