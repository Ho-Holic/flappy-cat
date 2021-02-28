// engine
#include "Vertex.hpp"

Vertex::Vertex(const Position& position, const Color& color)
    : m_position(position)
    , m_color(color)
{
    //
}

Vertex::Vertex()
    : Vertex(Position(0, 0), Color(0x000000ff))
{
}

const Position& Vertex::position() const
{

    return m_position;
}

const Color& Vertex::color() const
{

    return m_color;
}
