#pragma once

// engine
#include <core/Geometry.hpp>
#include <core/Signal.hpp>

class CircleGeometry : public Geometry {
public:
    using OnUpdateSignal = Signal<void()>;

public:
    CircleGeometry(float radius, std::size_t resolution);
    CircleGeometry();

public:
    OnUpdateSignal& onUpdate();
    void setResolution(std::size_t resolution);
    void setRadius(float radius);
    float radius() const;

public:
    size_type points() const override;
    vec2 pointAt(size_type index) const override;

    void setOrigin(const vec2& position) override;
    const vec2& origin() const override;

private:
    float m_radius;
    std::size_t m_resolution;
    vec2 m_origin;
    OnUpdateSignal m_onUpdate;
};
