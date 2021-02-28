#pragma once

// engine
#include <core/Shape.hpp>
#include <prototype/FlatTransformation.hpp>
#include <prototype/VertexBasedRender.hpp>

template <typename GeometryType>
class ShapeConstructor : public Shape {
public:
    template <typename... Args>
    ShapeConstructor(const Position& position, Args... args);
    ShapeConstructor();

public:
    void setColor(const Color& color);
    const Color& color() const;

public:
    virtual GeometryType& geometry() override;
    virtual FlatTransformation& transformation() override;
    virtual VertexBasedRender& render() override;

    virtual const GeometryType& geometry() const override;
    virtual const FlatTransformation& transformation() const override;
    virtual const VertexBasedRender& render() const override;

private:
    void update();

private:
    FlatTransformation mTransformation;
    GeometryType mGeometry;
    VertexBasedRender mRender;
    Color m_color;
};

template <typename GeometryType>
template <typename... Args>
ShapeConstructor<GeometryType>::ShapeConstructor(const Position& position, Args... args)
    : Shape()
    , mTransformation(position)
    , mGeometry(args...)
    , mRender()
    , m_color()
{
    mGeometry.onUpdate().connect(std::bind(&ShapeConstructor<GeometryType>::update, this));
    mTransformation.onUpdate().connect(std::bind(&ShapeConstructor<GeometryType>::update, this));
    update();
}

template <typename GeometryType>
ShapeConstructor<GeometryType>::ShapeConstructor()
    : ShapeConstructor(Position(0.f, 0.f))
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
    return mGeometry;
}

template <typename GeometryType>
FlatTransformation& ShapeConstructor<GeometryType>::transformation()
{
    return mTransformation;
}

template <typename GeometryType>
VertexBasedRender& ShapeConstructor<GeometryType>::render()
{
    return mRender;
}

template <typename GeometryType>
const GeometryType& ShapeConstructor<GeometryType>::geometry() const
{
    return mGeometry;
}

template <typename GeometryType>
const FlatTransformation& ShapeConstructor<GeometryType>::transformation() const
{
    return mTransformation;
}

template <typename GeometryType>
const VertexBasedRender& ShapeConstructor<GeometryType>::render() const
{
    return mRender;
}

template <typename GeometryType>
void ShapeConstructor<GeometryType>::update()
{
    render().update(*this);
}
