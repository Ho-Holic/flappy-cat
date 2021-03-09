#pragma once

#include "entity/FlappyCatStateNode.hpp"
#include <prototype/RectangleShape.hpp>

class FlappyCatViewLimit : public FlappyCatStateNode<FlappyCatViewLimit> {
public:
    FlappyCatViewLimit(const FlappyCatGameConstants& gameConstants);

public:
    void drawOn(const Window& window, const Transformation& transformation) const override;

private:
    void syncChildren() override;

private:
    RectangleShape m_top;
    RectangleShape m_topRight;
    RectangleShape m_right;
    RectangleShape m_bottomRight;
    RectangleShape m_bottom;
    RectangleShape m_bottomLeft;
    RectangleShape m_left;
    RectangleShape m_topLeft;
};
