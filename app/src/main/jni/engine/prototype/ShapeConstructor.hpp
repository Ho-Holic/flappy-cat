#pragma once

// engine
#include <core/Shape.hpp>
#include <prototype/FlatTransformation.hpp>
#include <prototype/VertexBasedRender.hpp>

template <typename GeometryType>
class ShapeConstructor : public Shape {
public:
    template <typename... Args>
    ShapeConstructor(const vec2& position, Args... args);
    ShapeConstructor();

public:
    void setColor(const Color& color);
    const Color& color() const;

public:
    GeometryType& geometry() override;
    FlatTransformation& transformation() override;
    VertexBasedRender& render() override;

    const GeometryType& geometry() const override;
    const FlatTransformation& transformation() const override;
    const VertexBasedRender& render() const override;

private:
    void update();

private:
    FlatTransformation m_transformation;
    GeometryType m_geometry;
    VertexBasedRender m_render;
    Color m_color;
};

template <typename GeometryType>
template <typename... Args>
ShapeConstructor<GeometryType>::ShapeConstructor(const vec2& position, Args... args)
    : Shape()
    , m_transformation(position)
    , m_geometry(args...)
    , m_render()
    , m_color()
{
    m_geometry.onUpdate().connect(std::bind(&ShapeConstructor<GeometryType>::update, this));
    m_transformation.onUpdate().connect(std::bind(&ShapeConstructor<GeometryType>::update, this));
    update();
}

template <typename GeometryType>
ShapeConstructor<GeometryType>::ShapeConstructor()
    : ShapeConstructor(vec2(0.f, 0.f))
{
    //
}

template <typename GeometryType>
void ShapeConstructor<GeometryType>::setColor(const Color& color)
{
    render().setBrushColor(color);
    //
    // TODO: Create loop for coloring
    //
    // Remove this 'update' and add 'foreach' to render and set correct color for vertex
    // update takes extra time to update position that does not changed
    //
    update();
}

template <typename GeometryType>
const Color& ShapeConstructor<GeometryType>::color() const
{
    return m_color;
}

template <typename GeometryType>
GeometryType& ShapeConstructor<GeometryType>::geometry()
{
    return m_geometry;
}

template <typename GeometryType>
FlatTransformation& ShapeConstructor<GeometryType>::transformation()
{
    return m_transformation;
}

template <typename GeometryType>
VertexBasedRender& ShapeConstructor<GeometryType>::render()
{
    return m_render;
}

template <typename GeometryType>
const GeometryType& ShapeConstructor<GeometryType>::geometry() const
{
    return m_geometry;
}

template <typename GeometryType>
const FlatTransformation& ShapeConstructor<GeometryType>::transformation() const
{
    return m_transformation;
}

template <typename GeometryType>
const VertexBasedRender& ShapeConstructor<GeometryType>::render() const
{
    return m_render;
}

template <typename GeometryType>
void ShapeConstructor<GeometryType>::update()
{
    render().update(*this);
}
