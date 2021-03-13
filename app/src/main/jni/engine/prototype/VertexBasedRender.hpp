#pragma once

#include <core/Render.hpp>
#include <core/Vertices.hpp>

class VertexBasedRender : public Render {
public:
    VertexBasedRender();

public:
    void setBrushColor(const Color& color);
    const Color& getBrushColor() const;
    void setDrawCenter(bool enabled);

public:
    void update(const Shape& shape) override;
    void drawOn(const Window& window, const RenderContext& renderContext) const override;

private:
    vec2 m_center;
    Vertices m_vertices;
    Color m_brushColor;

    bool m_drawCenter = false;
};
