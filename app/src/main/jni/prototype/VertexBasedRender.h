#ifndef FLAPPY_CAT_VERTEXBASEDRENDER_H
#define FLAPPY_CAT_VERTEXBASEDRENDER_H

// self
#include <core/Render.h>
#include <core/Vertices.h>

class VertexBasedRender : public Render {
public:
  VertexBasedRender();

public:
  void setBrushColor(const Color& color);

public:
  virtual void update(const Shape& shape) override;
  virtual void drawOn(const Window& window, const Transformation& transformation) const override;

private:
  Vertices mVertices;
  Color mBrushColor;
};


#endif //FLAPPY_CAT_VERTEXBASEDRENDER_H
