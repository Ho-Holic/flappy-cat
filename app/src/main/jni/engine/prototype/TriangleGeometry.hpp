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

    void setOrigin(const vec2& position) override;
    const vec2& origin() const override;

private:
    vec2 m_size;
    vec2 m_origin;
    OnUpdateSignal m_onUpdate;
};
