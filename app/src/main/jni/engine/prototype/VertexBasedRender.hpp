#pragma once

#include <core/Render.hpp>
#include <core/Vertices.hpp>

class VertexBasedRender : public Render {
public:
    VertexBasedRender();

public:
    void setBrushColor(const Color& color);
    const Color& getBrushColor() const;

public:
    void update(const Shape& shape) override;
    void drawOn(const Window& window, const RenderContext& renderContext) const override;

private:
    Vertices m_vertices;
    Color m_brushColor;
};
