#pragma once

// engine
#include "Color.hpp"
#include "Position.hpp"

class Vertex {
public:
    Vertex(const Position& position, const Color& color);
    Vertex();

public:
    const Position& position() const;
    const Color& color() const;

private:
    Position m_position;
    Color m_color;
};
