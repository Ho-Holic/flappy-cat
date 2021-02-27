#include "FlappyCatHero.hpp"
#include <core/Log.hpp>
#include <prototype/RectangleShape.hpp>
#include <prototype/TriangleShape.hpp>

FlappyCatHero::FlappyCatHero(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatHero>(gameConstants)
    , mJumpAcceleration()
    , mJumpVelocity()
    , mBall()
    , mMascot(gameConstants)
{
    //
}

void FlappyCatHero::reset()
{
    mBallBody.reset();
    FlappyCatStateNode<FlappyCatHero>::reset();
}

void FlappyCatHero::update(const FrameDuration& frameDuration)
{
    float time = std::chrono::duration_cast<GameSecond>(frameDuration).count();
    mBallBody.update(time);

    FlappyCatStateNode<FlappyCatHero>::update(frameDuration);
}

float FlappyCatHero::radius() const
{
    return mBall.geometry().radius();
}

void FlappyCatHero::setGravity(const Position& gravity)
{
    mBallBody.setGravity(gravity);
}

void FlappyCatHero::setRadius(float radius)
{
    mBall.geometry().setRadius(radius);
    syncChildren();
}

void FlappyCatHero::drawOn(const Window& window) const
{
    window.draw(mBall);
    mMascot.drawOn(window);
}

void FlappyCatHero::setColor(const Color& backgroundColor,
    const Color& bodyColor,
    const Color& scarfColor,
    const Color& mouthColor)
{
    mBall.setColor(backgroundColor);
    mMascot.setColor(bodyColor, scarfColor, mouthColor);
}

void FlappyCatHero::setJumpConstants(const Position& acceleration, const Position& velocity)
{
    mJumpAcceleration = acceleration;
    mJumpVelocity = velocity;
}

void FlappyCatHero::jump()
{
    mBallBody.setAcceleration(mJumpAcceleration);
    mBallBody.setVelocity(mJumpVelocity);
}

const Position& FlappyCatHero::distance() const
{
    return mBallBody.distance();
}

void FlappyCatHero::syncChildren()
{
    //
    // TODO: add rotation to mBall
    // Currently origin of ball is not in the center of the ball
    // so rotation would cause bad render, fix origin code
    // and uncomment rotation line
    //
    // mBall.transformation().setRotation(mAngle);
    //

    mBall.transformation().setPosition(position());

    float diameter = mBall.geometry().radius() * 2.f;

    Position mascotPos = mBall.transformation().position()
        + Position(diameter * 0.25f, diameter * 0.3f);

    mMascot.moveTo(mascotPos);
    mMascot.resize(Position(diameter, diameter));
    mMascot.rotateTo(rotation());
}
