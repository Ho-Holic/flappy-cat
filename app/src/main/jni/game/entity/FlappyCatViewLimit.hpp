#pragma once

#include "entity/FlappyCatStateNode.hpp"
#include <prototype/RectangleShape.hpp>

class FlappyCatViewLimit : public FlappyCatStateNode<FlappyCatViewLimit> {
public:
    FlappyCatViewLimit(const FlappyCatGameConstants& gameConstants);

public:
    void drawOn(const Window& window) const override;

private:
    void syncChildren() override;

private:
    RectangleShape mTop;
    RectangleShape mTopRight;
    RectangleShape mRight;
    RectangleShape mBottomRight;
    RectangleShape mBottom;
    RectangleShape mBottomLeft;
    RectangleShape mLeft;
    RectangleShape mTopLeft;
};
