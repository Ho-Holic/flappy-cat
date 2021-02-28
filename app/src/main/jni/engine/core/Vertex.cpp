// engine
#include "Vertex.hpp"

Vertex::Vertex(const Position& position, const Color& color)
    : mPosition(position)
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

    return mPosition;
}

const Color& Vertex::color() const
{

    return m_color;
}
