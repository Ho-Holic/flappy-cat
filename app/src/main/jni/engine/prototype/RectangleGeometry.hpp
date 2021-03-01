#pragma once

// engine
#include <core/Geometry.hpp>
#include <core/Signal.hpp>

class RectangleGeometry : public Geometry {
public:
    using OnUpdateSignal = Signal<void()>;

public:
    RectangleGeometry(const vec2& size);
    RectangleGeometry();

public:
    OnUpdateSignal& onUpdate();
    void resize(const vec2& size);
    const vec2& size() const;

public:
    virtual size_type points() const override;
    virtual vec2 pointAt(size_type index) const override;

private:
    vec2 m_size;
    OnUpdateSignal m_onUpdate;
};
