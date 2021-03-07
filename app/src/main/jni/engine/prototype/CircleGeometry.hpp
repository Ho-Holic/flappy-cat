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

private:
    float m_radius;
    std::size_t m_resolution;
    OnUpdateSignal m_onUpdate;
};
