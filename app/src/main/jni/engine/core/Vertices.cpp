// engine
#include "Vertices.hpp"

Vertices::Vertices()
  : mVertices() {
  //
}

size_t Vertices::size() const {

  return mVertices.size();
}

const Vertex& Vertices::operator [] (std::size_t index) const {

  return mVertices[index];
}

Vertices& Vertices::operator << (const Vertex& vertex) {

  mVertices.push_back(vertex);
  return *this;
}

void Vertices::reset() {
  mVertices.resize(0);
}











