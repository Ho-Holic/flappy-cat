// engine
#include "Vertex.hpp"

Vertex::Vertex(const vec2& position, const Color& color)
    : m_position(position)
    , m_color(color)
{
    //
}

Vertex::Vertex()
    : Vertex(vec2(0, 0), Color(0x000000ff))
{
}

const vec2& Vertex::position() const
{

    return m_position;
}

const Color& Vertex::color() const
{

    return m_color;
}
