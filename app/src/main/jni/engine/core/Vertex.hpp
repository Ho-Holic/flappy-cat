#pragma once

// engine
#include "Color.hpp"
#include <math/vec2.hpp>

class Vertex {
public:
    Vertex(const vec2& position, const Color& color);
    Vertex();

public:
    const vec2& position() const;
    const Color& color() const;

private:
    vec2 m_position;
    Color m_color;
};
