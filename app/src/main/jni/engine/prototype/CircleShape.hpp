#pragma once

// engine
#include <core/Shape.hpp>
#include <prototype/CircleGeometry.hpp>
#include <prototype/FlatTransformation.hpp>
#include <prototype/VertexBasedRender.hpp>

class CircleShape : public Shape {
public:
    CircleShape(const Position& position, float radius, std::size_t resolution);
    CircleShape();

public:
    void setColor(const Color& color);

public:
    virtual CircleGeometry& geometry() override;
    virtual FlatTransformation& transformation() override;
    virtual VertexBasedRender& render() override;

    virtual const CircleGeometry& geometry() const override;
    virtual const FlatTransformation& transformation() const override;
    virtual const VertexBasedRender& render() const override;

private:
    void update();

private:
    FlatTransformation mTransformation;
    CircleGeometry mGeometry;
    VertexBasedRender mRender;
    Color mColor;
};
