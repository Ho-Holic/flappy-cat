#pragma once

// stl
#include <cstddef>

// engine
#include "Position.hpp"

class Geometry {
public:
    typedef std::size_t size_type;

public:
    virtual ~Geometry() = default;

public:
    virtual size_type points() const = 0;
    virtual Position pointAt(size_type index) const = 0;
};
