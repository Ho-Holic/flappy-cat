
// self
#include "VertexBasedRender.h"
#include <core/Window.h>

VertexBasedRender::VertexBasedRender()
: Render()
, mVertices() {
  //
}

void VertexBasedRender::drawOn(const Window& window) const {

  window.drawVertices(mVertices);
}

void VertexBasedRender::update(const Shape &shape) {

}





