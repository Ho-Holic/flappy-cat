#pragma once

#include "entity/FlappyCatStateNode.hpp"
#include <memory>
#include <prototype/RectangleShape.hpp>
#include <prototype/TriangleShape.hpp>

class FlappyCatMascot : public FlappyCatStateNode<FlappyCatMascot> {
public:
    FlappyCatMascot(const FlappyCatGameConstants& gameConstants);

public:
    void drawOn(const Window& window, const Transformation& transformation) const override;

public:
    void setColor(const Color& bodyColor,
        const Color& scarfColor,
        const Color& mouthColor);
    std::vector<std::shared_ptr<Geometry>> duplicateParts() const;

private:
    void syncChildren() override;

private:
    RectangleShape m_body;
    RectangleShape m_backLeg;
    RectangleShape m_frontLeg;
    RectangleShape m_tail;
    RectangleShape m_scarf;
    RectangleShape m_scarfTail;
    RectangleShape m_head;
    TriangleShape m_leftEar;
    TriangleShape m_rightEar;
    RectangleShape m_leftEye;
    RectangleShape m_rightEye;
    RectangleShape m_mouth;
};
