#pragma once

#include "FlappyCatMascot.hpp"
#include "entity/FlappyCatStateNode.hpp"
#include <physics/PhysicsBody.hpp>
#include <prototype/CircleShape.hpp>

class FlappyCatHero : public FlappyCatStateNode<FlappyCatHero> {
public:
    using jump_modifier_type = std::function<void(entity_type&)>;

public:
    FlappyCatHero(const FlappyCatGameConstants& gameConstants);

public:
    void reset() override;
    void update(const FrameDuration& frameDuration) override;
    void drawOn(const Window& window) const override;

public:
    void setColor(const Color& backgroundColor,
        const Color& bodyColor,
        const Color& scarfColor,
        const Color& mouthColor);

    void setRadius(float radius);
    float radius() const;

    void setJumpModifier(jump_modifier_type modifier);
    void setGravity(const Position& gravity);
    void setJumpConstants(const Position& acceleration, const Position& velocity);
    void jump();
    const Position& distance() const;

private:
    void syncChildren() override;

private:
    Position m_jumpAcceleration;
    Position m_jumpVelocity;
    CircleShape m_ball;
    PhysicsBody m_ballBody;
    FlappyCatMascot m_mascot;
    jump_modifier_type m_jumpModifier;
};
