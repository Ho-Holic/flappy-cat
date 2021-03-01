#pragma once

// stl
#include <cstddef>

// engine
#include <math/vec2.hpp>

class Geometry {
public:
    typedef std::size_t size_type;

public:
    virtual ~Geometry() = default;

public:
    virtual size_type points() const = 0;
    virtual vec2 pointAt(size_type index) const = 0;
};
