#pragma once

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
    const vec2& origin() const override;
    const vec2& position() const override;
    const vec2& scale() const override;
    float rotation() const override;

    void setOrigin(const vec2& origin) override;
    void setPosition(const vec2& position) override;
    void setScale(const vec2& factor) override;
    void setRotation(float angle) override;

private:
    vec2 m_position;
    vec2 m_origin;
    vec2 m_scale;
    float m_angle;
    OnUpdateSignal m_onUpdate;
};
