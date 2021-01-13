#pragma once

// engine
#include <core/Shape.hpp>
#include <prototype/FlatTransformation.hpp>
#include <prototype/RectangleGeometry.hpp>
#include <prototype/VertexBasedRender.hpp>

class RectangleShape : public Shape {
public:
    RectangleShape(const Position& position, const Position& size);
    RectangleShape();

public:
    void setColor(const Color& color);
    const Color& color() const;

public:
    virtual RectangleGeometry& geometry() override;
    virtual FlatTransformation& transformation() override;
    virtual VertexBasedRender& render() override;

    virtual const RectangleGeometry& geometry() const override;
    virtual const FlatTransformation& transformation() const override;
    virtual const VertexBasedRender& render() const override;

private:
    void update();

private:
    FlatTransformation mTransformation;
    RectangleGeometry mGeometry;
    VertexBasedRender mRender;
};
