#pragma once

//engine
#include "Vertex.hpp"

// stl
#include <cstdint>
#include <vector>

class Vertices {
public:
    Vertices();

public:
    const Vertex& operator[](std::size_t index) const;
    Vertices& operator<<(const Vertex& vertex);

public:
    size_t size() const;
    void reset();

private:
    std::vector<Vertex> m_vertices;
};
