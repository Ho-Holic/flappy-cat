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

void VertexBasedRender::drawOn(const Window& window, const Transformation& transformation) const
{
    window.drawVertices(m_vertices, transformation);
}

void VertexBasedRender::update(const Shape& shape)
{

    Geometry::size_type points = shape.geometry().points();

    // TODO: not optimal, create more clever approach later
    m_vertices.reset();

    if (points < 3) { // give me some love <3
        return;
    }

    for (Geometry::size_type index = 0; index < points; ++index) {

        // TODO: remove this part and make transform matrix
        // rotate
        float angle = shape.transformation().rotation();

        float sinValue = std::sin(angle);
        float cosValue = std::cos(angle);

        vec2 p = shape.geometry().pointAt(index) - shape.transformation().origin();

        float rotatedX = p.x * cosValue - p.y * sinValue;
        float rotatedY = p.x * sinValue + p.y * cosValue;

        //
        // TODO: add scale/origin later
        //
        // When object is moved, origin doesn't take into account
        // only for rotation.
        //
        // Scale is implemented only for 'View' to change all objects
        // representation on the screen, but local scale is not implemented
        //

        m_vertices << Vertex(shape.transformation().position()
                + vec2(rotatedX, rotatedY)
                + shape.transformation().origin(),
            m_brushColor);
    }
}

const Color& VertexBasedRender::getBrushColor() const
{
    return m_brushColor;
}
