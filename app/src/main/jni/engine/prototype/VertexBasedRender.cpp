#include "VertexBasedRender.hpp"
#include <cmath>
#include <core/Log.hpp>
#include <core/Shape.hpp>
#include <core/Window.hpp>

VertexBasedRender::VertexBasedRender()
    : Render()
    , m_vertices()
    , m_brushColor()
{
    //
}

void VertexBasedRender::setBrushColor(const Color& color)
{
    m_brushColor = color;
}

void VertexBasedRender::drawOn(const Window& window, const RenderContext& renderContext) const
{
    window.drawVertices(m_vertices, renderContext);

    if (m_drawCenter) {
        window.drawPoint(Vertex(m_center, Color(255, 0, 0)), renderContext);
    }
}

void VertexBasedRender::update(const Shape& shape)
{
    m_center = shape.transformation().position();

    Geometry::size_type points = shape.geometry().points();

    // TODO: not optimal, create more clever approach later
    m_vertices.reset();

    if (points < 3) { // give me some love <3
        return;
    }

    for (Geometry::size_type index = 0; index < points; ++index) {

        auto p = to_mat3(shape.transformation()) * vec3(shape.geometry().pointAt(index), 1.f);

        m_vertices << Vertex(vec2(p.x, p.y), m_brushColor);
    }
}

const Color& VertexBasedRender::getBrushColor() const
{
    return m_brushColor;
}

void VertexBasedRender::setDrawCenter(bool enabled)
{
    m_drawCenter = enabled;
}
