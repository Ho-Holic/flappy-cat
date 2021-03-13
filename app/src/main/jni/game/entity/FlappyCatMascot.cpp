#include "FlappyCatMascot.hpp"
#include <core/View.hpp>

FlappyCatMascot::FlappyCatMascot(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatMascot>(gameConstants)
    , m_body()
    , m_backLeg()
    , m_frontLeg()
    , m_tail()
    , m_scarf()
    , m_scarfTail()
    , m_head()
    , m_leftEar()
    , m_rightEar()
    , m_leftEye()
    , m_rightEye()
    , m_mouth()
{
    //
}

void FlappyCatMascot::drawOn(const Window& window, const RenderContext& renderContext) const
{
    // TODO: make Transform inside Entity to avoid this View reconstruction
    View mascotView;
    mascotView.setPosition(this->position());
    mascotView.setRotation(this->rotation());
    mascotView.setScale(vec2(1.f, 1.f));

    RenderContext newRenderContext { renderContext.transformation * to_mat3(mascotView) };

    m_body.render().drawOn(window, newRenderContext);
    m_backLeg.render().drawOn(window, newRenderContext);
    m_frontLeg.render().drawOn(window, newRenderContext);
    m_tail.render().drawOn(window, newRenderContext);
    m_scarf.render().drawOn(window, newRenderContext);
    m_scarfTail.render().drawOn(window, newRenderContext);
    m_head.render().drawOn(window, newRenderContext);
    m_leftEar.render().drawOn(window, newRenderContext);
    m_rightEar.render().drawOn(window, newRenderContext);
    m_leftEye.render().drawOn(window, newRenderContext);
    m_rightEye.render().drawOn(window, newRenderContext);
    m_mouth.render().drawOn(window, newRenderContext);
}

void FlappyCatMascot::syncChildren()
{
    vec2 referenceSize(2000.f, 2000.f); // must be equal, 2000x2000 square

    vec2 scale = size() / referenceSize;

    // relation between parts
    vec2 bodyPos = vec2(0.f, 0.f);

    vec2 bodySize(1000.f, 500.f);
    vec2 headPos(660.f, 340.f);
    vec2 headSize(570.f, 440.f);
    vec2 backLegPos(0.f, -375.f);
    vec2 frontLegPos(625.f, 0.f);
    vec2 legAndTailSize(150.f, 500.f);
    vec2 tailPos(0.f, 250.f);
    vec2 earSize(200.f, 375.f);
    vec2 leftEarPos(0.f, headSize.y); // 0.f, 440.f
    vec2 rightEarPos(headSize.x - earSize.x, 0.f); // 360.f, 0
    vec2 eyeSize(145.f, 145.f);
    vec2 leftEyePos(80.f, 200.f);
    vec2 rightEyePos(300.f, 0.f);
    vec2 scarfSize(750.f, 210.f);
    vec2 scarfPos(400.f, 210.f);
    vec2 scarfTailSize(150.f, 315.f);
    vec2 scarfTailPos(75.f, -148.f);
    vec2 mouthSize(56.f, 36.f);
    vec2 mouthPos(280.f, 96.f);

    vec2 center(bodySize.x / 2.f, bodySize.y / 2.f);

    // move
    vec2 bodyPosRes = bodyPos - center;
    vec2 headPosRes = bodyPos + headPos - center;
    vec2 backLegPosRes = bodyPos + backLegPos - center;
    vec2 frontLegPosRes = bodyPos + backLegPos + frontLegPos - center;
    vec2 tailPosRes = bodyPos + tailPos - center;
    vec2 leftEarPosRes = bodyPos + headPos + leftEarPos - center;
    vec2 rightEarPosRes = bodyPos + headPos + leftEarPos + rightEarPos - center;

    vec2 leftEyePosRes = bodyPos + headPos + leftEyePos - center;
    vec2 rightEyePosRes = bodyPos + headPos + leftEyePos + rightEyePos - center;

    vec2 scarfPosRes = bodyPos + scarfPos - center;
    vec2 scarfTailPosRes = bodyPos + scarfPos + scarfTailPos - center;
    vec2 mouthPosRes = bodyPos + headPos + mouthPos - center;

    // place objects

    m_body.transformation().setPosition(bodyPosRes * scale);
    m_head.transformation().setPosition(headPosRes * scale);
    m_backLeg.transformation().setPosition(backLegPosRes * scale);
    m_frontLeg.transformation().setPosition(frontLegPosRes * scale);
    m_tail.transformation().setPosition(tailPosRes * scale);
    m_leftEar.transformation().setPosition(leftEarPosRes * scale);
    m_rightEar.transformation().setPosition(rightEarPosRes * scale);
    m_leftEye.transformation().setPosition(leftEyePosRes * scale);
    m_rightEye.transformation().setPosition(rightEyePosRes * scale);
    m_scarf.transformation().setPosition(scarfPosRes * scale);
    m_scarfTail.transformation().setPosition(scarfTailPosRes * scale);
    m_mouth.transformation().setPosition(mouthPosRes * scale);

    // resize objects
    m_body.geometry().resize(bodySize * scale);
    m_head.geometry().resize(headSize * scale);
    m_backLeg.geometry().resize(legAndTailSize * scale);
    m_frontLeg.geometry().resize(legAndTailSize * scale);
    m_tail.geometry().resize(legAndTailSize * scale);
    m_leftEar.geometry().resize(earSize * scale);
    m_rightEar.geometry().resize(earSize * scale);
    m_leftEye.geometry().resize(eyeSize * scale);
    m_rightEye.geometry().resize(eyeSize * scale);
    m_scarf.geometry().resize(scarfSize * scale);
    m_scarfTail.geometry().resize(scarfTailSize * scale);
    m_mouth.geometry().resize(mouthSize * scale);
}

void FlappyCatMascot::setColor(const Color& bodyColor,
    const Color& scarfColor,
    const Color& mouthColor)
{
    m_body.setColor(bodyColor);
    m_backLeg.setColor(bodyColor);
    m_frontLeg.setColor(bodyColor);
    m_tail.setColor(bodyColor);
    m_head.setColor(bodyColor);
    m_leftEar.setColor(bodyColor);
    m_rightEar.setColor(bodyColor);

    m_scarf.setColor(scarfColor);
    m_scarfTail.setColor(scarfColor);
    m_leftEye.setColor(scarfColor);
    m_rightEye.setColor(scarfColor);

    m_mouth.setColor(mouthColor);
}
