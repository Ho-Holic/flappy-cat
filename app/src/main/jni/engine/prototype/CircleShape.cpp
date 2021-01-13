// engine
#include "CircleShape.hpp"

CircleShape::CircleShape(const Position& position, float radius, std::size_t resolution)
    : Shape()
    , mTransformation(position)
    , mGeometry(radius, resolution)
    , mRender()
    , mColor()
{
    mGeometry.onUpdate().connect(std::bind(&CircleShape::update, this));
    mTransformation.onUpdate().connect(std::bind(&CircleShape::update, this));
    update();
}

CircleShape::CircleShape()
    : CircleShape(Position(0.f, 0.f), 1.f, 32u)
{
    //
}

void CircleShape::setColor(const Color& color)
{

    render().setBrushColor(color);
    /* TODO: Create loop for coloring
   * Remove this 'update' and add 'foreach' to render and set correct color for vertex
   * update takes extra time to update position that does not changed
   */
    update();
}

CircleGeometry& CircleShape::geometry()
{
    return mGeometry;
}

FlatTransformation& CircleShape::transformation()
{
    return mTransformation;
}

VertexBasedRender& CircleShape::render()
{
    return mRender;
}

const CircleGeometry& CircleShape::geometry() const
{
    return mGeometry;
}

const FlatTransformation& CircleShape::transformation() const
{
    return mTransformation;
}

const VertexBasedRender& CircleShape::render() const
{
    return mRender;
}

void CircleShape::update()
{
    render().update(*this);
}
