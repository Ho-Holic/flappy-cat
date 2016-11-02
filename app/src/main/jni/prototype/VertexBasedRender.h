#ifndef FLAPPY_CAT_VERTEXBASEDRENDER_H
#define FLAPPY_CAT_VERTEXBASEDRENDER_H

// self
#include <core/Render.h>
#include <core/Vertices.h>

class VertexBasedRender : public Render {
public:
  VertexBasedRender();
private:
  Vertices mVertices;
};


#endif //FLAPPY_CAT_VERTEXBASEDRENDER_H
