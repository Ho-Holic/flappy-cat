#pragma once

#include "entity/FlappyCatStateNode.hpp"
#include <memory>
#include <prototype/RectangleShape.hpp>
#include <prototype/TriangleShape.hpp>

class FlappyCatMascot : public FlappyCatStateNode<FlappyCatMascot> {
public:
    FlappyCatMascot(const FlappyCatGameConstants& gameConstants);

public:
    void drawOn(const Window& window) const override;

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
    RectangleShape mTail;
    RectangleShape mScarf;
    RectangleShape mScarfTail;
    RectangleShape m_head;
    TriangleShape m_leftEar;
    TriangleShape mRightEar;
    RectangleShape m_leftEye;
    RectangleShape mRightEye;
    RectangleShape m_mouth;
};
