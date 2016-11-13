#ifndef FLAPPY_CAT_VERTEXBASEDRENDER_H
#define FLAPPY_CAT_VERTEXBASEDRENDER_H

// self
#include <core/Render.h>
#include <core/Vertices.h>

class VertexBasedRender : public Render {
public:
  VertexBasedRender();
public:
  virtual void update(const Shape& shape) override;
  virtual void drawOn(const Window& window) const override;

private:
  Vertices mVertices;
};


#endif //FLAPPY_CAT_VERTEXBASEDRENDER_H
