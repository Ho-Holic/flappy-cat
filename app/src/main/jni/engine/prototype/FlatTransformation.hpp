#pragma once

// engine
#include <core/Signal.hpp>
#include <core/Transformation.hpp>

class FlatTransformation : public Transformation {
public:
    using OnUpdateSignal = Signal<void()>;

public:
    FlatTransformation(const vec2& position);
    FlatTransformation();

public:
    OnUpdateSignal& onUpdate();

public:
    virtual const vec2& origin() const override;
    virtual const vec2& position() const override;
    virtual const vec2& scale() const override;
    virtual float rotation() const override;

    virtual void setOrigin(const vec2& origin) override;
    virtual void setPosition(const vec2& position) override;
    virtual void setScale(const vec2& factor) override;
    virtual void setRotation(float angle) override;

private:
    vec2 m_position;
    vec2 m_origin;
    vec2 m_scale;
    float m_angle;
    OnUpdateSignal m_onUpdate;
};
