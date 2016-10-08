// self
#include "AndroidVertices.h"

AndroidVertices::AndroidVertices()
  : mVertices() {
  //
}

size_t AndroidVertices::size() const {

  return mVertices.size();
}

const AndroidVertex& AndroidVertices::operator [] (std::size_t index) const {

  return mVertices[index];
}

AndroidVertices& AndroidVertices::operator << (const AndroidVertex& vertex) {

  mVertices.push_back(vertex);
  return *this;
}









