#pragma once

// engine
#include <math/vec2.hpp>

class Transformation {
public:
    virtual ~Transformation() = default;

public:
    // TODO: setOrigin currently affects only rotation, change this later
    virtual void setOrigin(const vec2& position) = 0;
    virtual void setPosition(const vec2& position) = 0;
    virtual void setScale(const vec2& factor) = 0;
    virtual void setRotation(float angle) = 0;

    virtual const vec2& origin() const = 0;
    virtual const vec2& position() const = 0;
    virtual const vec2& scale() const = 0;
    virtual float rotation() const = 0;
};
