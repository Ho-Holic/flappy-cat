#pragma once

// engine
#include "Position.hpp"

class Transformation {
public:
    virtual ~Transformation() = default;

public:
    // TODO: setOrigin currently affects only rotation, change this later
    virtual void setOrigin(const Position& position) = 0;
    virtual void setPosition(const Position& position) = 0;
    virtual void setScale(const Position& factor) = 0;
    virtual void setRotation(float angle) = 0;

    virtual const Position& origin() const = 0;
    virtual const Position& position() const = 0;
    virtual const Position& scale() const = 0;
    virtual float rotation() const = 0;
};
