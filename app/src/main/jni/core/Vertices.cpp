// self
#include "Vertices.h"

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









