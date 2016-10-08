#ifndef FLAPPY_CAT_ANDROIDVERTICES_H
#define FLAPPY_CAT_ANDROIDVERTICES_H

//self
#include "AndroidVertex.h"

// stl
#include <cstdint>
#include <vector>


class AndroidVertices {
public:
  AndroidVertices();

public:
  const AndroidVertex& operator [] (std::size_t index) const;
  AndroidVertices& operator << (const AndroidVertex& vertex);

public:
  size_t size() const;

private:
  std::vector<AndroidVertex> mVertices;

};


#endif //FLAPPY_CAT_ANDROIDVERTICES_H
