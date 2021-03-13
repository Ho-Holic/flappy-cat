#pragma once

#include <core/Window.hpp>
#include <game/FlappyCatClock.hpp>
#include <game/FlappyCatGameConstants.hpp>

class FlappyCatEntity {
public:
    FlappyCatEntity(const FlappyCatGameConstants& gameConstants);
    virtual ~FlappyCatEntity();

public:
    virtual void initialize() = 0;
    virtual void reset() = 0;
    virtual void update(const FrameDuration& frameDuration) = 0;
    virtual void drawOn(const Window& window, const RenderContext& renderContext) const = 0;

    virtual const vec2& position() const;
    virtual float rotation() const;
    virtual const vec2& size() const;

    virtual void moveTo(const vec2& position);
    virtual void moveBy(const vec2& offset);

    virtual void resize(const vec2& size);
    virtual void rotateTo(float angle);

public:
    const FlappyCatGameConstants& gameConstants() const;

private:
    virtual void syncChildren();

private:
    const FlappyCatGameConstants& m_gameConstants;
    vec2 m_position;
    float m_angle;
    vec2 m_size;
};
