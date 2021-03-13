#include "FlappyCatHero.hpp"
#include <core/Log.hpp>
#include <prototype/RectangleShape.hpp>
#include <prototype/TriangleShape.hpp>

FlappyCatHero::FlappyCatHero(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatHero>(gameConstants)
    , m_jumpAcceleration()
    , m_jumpVelocity()
    , m_ball()
    , m_mascot(gameConstants)
{
    //
}

void FlappyCatHero::reset()
{
    m_ballBody.reset();
    FlappyCatStateNode<FlappyCatHero>::reset();
}

void FlappyCatHero::update(const FrameDuration& frameDuration)
{
    float time = std::chrono::duration_cast<GameSecond>(frameDuration).count();
    m_ballBody.update(time);

    FlappyCatStateNode<FlappyCatHero>::update(frameDuration);
}

float FlappyCatHero::radius() const
{
    return m_ball.geometry().radius();
}

void FlappyCatHero::setJumpModifier(jump_modifier_type modifier)
{
    m_jumpModifier = modifier;
}

void FlappyCatHero::setGravity(const vec2& gravity)
{
    m_ballBody.setGravity(gravity);
}

void FlappyCatHero::setRadius(float radius)
{
    m_ball.geometry().setRadius(radius);
    syncChildren();
}

void FlappyCatHero::drawOn(const Window& window, const RenderContext& renderContext) const
{
    m_ball.render().drawOn(window, renderContext);
    m_mascot.drawOn(window, renderContext);
}

void FlappyCatHero::setColor(const Color& backgroundColor,
    const Color& bodyColor,
    const Color& scarfColor,
    const Color& mouthColor)
{
    m_ball.setColor(backgroundColor);
    m_mascot.setColor(bodyColor, scarfColor, mouthColor);
}

void FlappyCatHero::setJumpConstants(const vec2& acceleration, const vec2& velocity)
{
    m_jumpAcceleration = acceleration;
    m_jumpVelocity = velocity;
}

void FlappyCatHero::jump()
{
    m_ballBody.setAcceleration(m_jumpAcceleration);
    m_ballBody.setVelocity(m_jumpVelocity);
    if (m_jumpModifier) {
        m_jumpModifier(*this);
    }
}

const vec2& FlappyCatHero::distance() const
{
    return m_ballBody.distance();
}

void FlappyCatHero::syncChildren()
{
    m_ball.transformation().setRotation(rotation());
    m_ball.transformation().setPosition(position());

    float diameter = m_ball.geometry().radius() * 2.f;

    m_mascot.moveTo(position());
    m_mascot.resize(vec2(diameter, diameter));
    m_mascot.rotateTo(rotation());
}
