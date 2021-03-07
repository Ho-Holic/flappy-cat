#pragma once

// engine
#include <core/Geometry.hpp>
#include <core/Signal.hpp>

class TriangleGeometry : public Geometry {
public:
    using OnUpdateSignal = Signal<void()>;

public:
    TriangleGeometry(const vec2& size);
    TriangleGeometry();

public:
    OnUpdateSignal& onUpdate();
    void resize(const vec2& size);
    const vec2& size() const;

public:
    size_type points() const override;
    vec2 pointAt(size_type index) const override;

private:
    vec2 m_size;
    OnUpdateSignal m_onUpdate;
};
