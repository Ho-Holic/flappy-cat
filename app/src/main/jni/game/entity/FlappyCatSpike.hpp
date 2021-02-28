#pragma once

#include "entity/FlappyCatStateNode.hpp"
#include <prototype/RectangleShape.hpp>

class FlappyCatSpike : public FlappyCatStateNode<FlappyCatSpike> {
public:
    FlappyCatSpike(const FlappyCatGameConstants& gameConstants);

public:
    void drawOn(const Window& window) const override;

public:
    void setColor(const Color& color);

private:
    void syncChildren() override;

private:
    RectangleShape m_spike;
};
