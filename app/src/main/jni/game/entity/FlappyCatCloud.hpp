#pragma once

#include "entity/FlappyCatStateNode.hpp"
#include <prototype/CircleShape.hpp>
#include <vector>

class FlappyCatCloud : public FlappyCatStateNode<FlappyCatCloud> {
public:
    FlappyCatCloud(const FlappyCatGameConstants& gameConstants);

public:
    void initialize() override;
    void drawOn(const Window& window) const override;

public:
    void setColor(const Color& color);
    void setParts(float parts);
    void foreachCloud(const std::function<void(CircleShape&)>& modifier);

public:
    float m_parts;
    std::vector<CircleShape> m_cloudParts;
};
