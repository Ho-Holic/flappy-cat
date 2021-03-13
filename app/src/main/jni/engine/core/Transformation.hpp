#pragma once

#include <math/mat3.hpp>
#include <math/vec2.hpp>

class Transformation {
public:
    virtual ~Transformation() = default;

public:
    virtual void setPosition(const vec2& position) = 0;
    virtual void setScale(const vec2& factor) = 0;
    virtual void setRotation(float angle) = 0;

    virtual const vec2& position() const = 0;
    virtual const vec2& scale() const = 0;
    virtual float rotation() const = 0;
};

mat3 to_mat3(const Transformation& transformation);
