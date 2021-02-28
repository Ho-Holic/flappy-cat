#pragma once

// engine
#include <core/Render.hpp>
#include <core/Vertices.hpp>

class VertexBasedRender : public Render {
public:
    VertexBasedRender();

public:
    void setBrushColor(const Color& color);
    const Color& getBrushColor() const;

public:
    virtual void update(const Shape& shape) override;
    virtual void drawOn(const Window& window, const Transformation& transformation) const override;

private:
    Vertices m_vertices;
    Color m_brushColor;
};
