#pragma once

#include <cstddef>
#include <math/vec2.hpp>

class Geometry {
public:
    typedef std::size_t size_type;

public:
    virtual ~Geometry() = default;

public:
    virtual size_type points() const = 0;
    virtual vec2 pointAt(size_type index) const = 0;

    virtual void setOrigin(const vec2& position) = 0;
    virtual const vec2& origin() const = 0;
};
