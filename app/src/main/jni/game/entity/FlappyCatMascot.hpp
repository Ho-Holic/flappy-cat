#pragma once

// engine
#include <prototype/RectangleShape.hpp>
#include <prototype/TriangleShape.hpp>

// stl
#include <memory>

// game
#include "FlappyCatEntity.hpp"

class FlappyCatMascot : public FlappyCatEntity {
public:
    FlappyCatMascot(const FlappyCatGameConstants& gameConstants);

public:
    virtual void drawOn(const Window& window) const override;

public:
    void setColor(const Color& bodyColor,
        const Color& scarfColor,
        const Color& mouthColor);
    std::vector<std::shared_ptr<Geometry>> duplicateParts() const;

private:
    virtual void syncChildren() override;

private:
    RectangleShape mBody;
    RectangleShape mBackLeg;
    RectangleShape mFrontLeg;
    RectangleShape mTail;
    RectangleShape mScarf;
    RectangleShape mScarfTail;
    RectangleShape mHead;
    TriangleShape mLeftEar;
    TriangleShape mRightEar;
    RectangleShape mLeftEye;
    RectangleShape mRightEye;
    RectangleShape mMouth;
};