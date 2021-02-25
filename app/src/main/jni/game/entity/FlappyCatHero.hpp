#pragma once

#include "FlappyCatMascot.hpp"
#include "entity/FlappyCatStateNode.hpp"
#include <prototype/CircleShape.hpp>

class FlappyCatHero : public FlappyCatStateNode<FlappyCatHero> {
public:
    FlappyCatHero(const FlappyCatGameConstants& gameConstants);

public:
    void drawOn(const Window& window) const override;

public:
    void setColor(const Color& backgroundColor,
        const Color& bodyColor,
        const Color& scarfColor,
        const Color& mouthColor);

    void setRadius(float radius);
    float radius() const;

    void setJumpConstants(const Position& acceleration, const Position& velocity);
    void jump();

private:
    void syncChildren() override;

private:
    Position mJumpAcceleration;
    Position mJumpVelocity;
    CircleShape mBall;
    FlappyCatMascot mMascot;
};
