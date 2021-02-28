// engine
#include "Vertices.hpp"

Vertices::Vertices()
    : m_vertices()
{
    //
}

size_t Vertices::size() const
{

    return m_vertices.size();
}

const Vertex& Vertices::operator[](std::size_t index) const
{

    return m_vertices[index];
}

Vertices& Vertices::operator<<(const Vertex& vertex)
{

    m_vertices.push_back(vertex);
    return *this;
}

void Vertices::reset()
{
    m_vertices.resize(0);
}
