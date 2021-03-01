#pragma once

// engine
#include <core/Signal.hpp>
#include <core/Transformation.hpp>

class View : public Transformation {
public:
    View();
    virtual ~View() = default;

public:
    virtual void setOrigin(const vec2& origin) override;
    // little hack here 'position' is 'size'
    virtual void setPosition(const vec2& position) override;
    virtual void setScale(const vec2& factor) override;
    virtual void setRotation(float angle) override;

    virtual const vec2& origin() const override;
    virtual const vec2& position() const override;
    virtual const vec2& scale() const override;
    virtual float rotation() const override;

public:
    vec2 m_origin;
    vec2 m_size;
    vec2 m_scale;
    float m_angle;
};
