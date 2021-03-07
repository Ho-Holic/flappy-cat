#pragma once

// engine
#include <core/Signal.hpp>
#include <core/Transformation.hpp>

class View : public Transformation {
public:
    View();
    virtual ~View() = default;

public:
    void setOrigin(const vec2& origin) override;
    // little hack here 'position' is 'size' from window resize event
    void setPosition(const vec2& position) override;
    void setScale(const vec2& factor) override;
    void setRotation(float angle) override;

    const vec2& origin() const override;
    const vec2& position() const override;
    const vec2& scale() const override;
    float rotation() const override;

public:
    vec2 m_origin;
    vec2 m_size;
    vec2 m_scale;
    float m_angle;
};
