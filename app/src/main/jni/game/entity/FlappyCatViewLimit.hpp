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
    RectangleShape m_bottomRight;
    RectangleShape m_bottom;
    RectangleShape m_bottomLeft;
    RectangleShape m_left;
    RectangleShape mTopLeft;
};
