#include "FlappyCatMascot.hpp"

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
    m_body.render().drawOn(window, renderContext);
    m_backLeg.render().drawOn(window, renderContext);
    m_frontLeg.render().drawOn(window, renderContext);
    m_tail.render().drawOn(window, renderContext);
    m_scarf.render().drawOn(window, renderContext);
    m_scarfTail.render().drawOn(window, renderContext);
    m_head.render().drawOn(window, renderContext);
    m_leftEar.render().drawOn(window, renderContext);
    m_rightEar.render().drawOn(window, renderContext);
    m_leftEye.render().drawOn(window, renderContext);
    m_rightEye.render().drawOn(window, renderContext);
    m_mouth.render().drawOn(window, renderContext);
}

void FlappyCatMascot::syncChildren()
{
    const vec2& pos = position();
    float angle = rotation();

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

    // move
    // TODO: later remove additional Res variables
    vec2 bodyPosRes = bodyPos;
    vec2 headPosRes = bodyPos + headPos;
    vec2 backLegPosRes = bodyPos + backLegPos;
    vec2 frontLegPosRes = bodyPos + backLegPos + frontLegPos;
    vec2 tailPosRes = bodyPos + tailPos;
    vec2 leftEarPosRes = bodyPos + headPos + leftEarPos;
    vec2 rightEarPosRes = bodyPos + headPos + leftEarPos + rightEarPos;

    vec2 leftEyePosRes = bodyPos + headPos + leftEyePos;
    vec2 rightEyePosRes = bodyPos + headPos + leftEyePos + rightEyePos;

    vec2 scarfPosRes = bodyPos + scarfPos;
    vec2 scarfTailPosRes = bodyPos + scarfPos + scarfTailPos;
    vec2 mouthPosRes = bodyPos + headPos + mouthPos;

    // place objects

    m_body.transformation().setPosition(pos + bodyPosRes * scale);
    m_head.transformation().setPosition(pos + headPosRes * scale);
    m_backLeg.transformation().setPosition(pos + backLegPosRes * scale);
    m_frontLeg.transformation().setPosition(pos + frontLegPosRes * scale);
    m_tail.transformation().setPosition(pos + tailPosRes * scale);
    m_leftEar.transformation().setPosition(pos + leftEarPosRes * scale);
    m_rightEar.transformation().setPosition(pos + rightEarPosRes * scale);
    m_leftEye.transformation().setPosition(pos + leftEyePosRes * scale);
    m_rightEye.transformation().setPosition(pos + rightEyePosRes * scale);
    m_scarf.transformation().setPosition(pos + scarfPosRes * scale);
    m_scarfTail.transformation().setPosition(pos + scarfTailPosRes * scale);
    m_mouth.transformation().setPosition(pos + mouthPosRes * scale);

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

    // rotate

    vec2 center(bodySize.x / 2.f, bodySize.y / 2.f);

    m_body.transformation().setOrigin((center - bodyPosRes) * scale);
    m_head.transformation().setOrigin((center - headPosRes) * scale);
    m_backLeg.transformation().setOrigin((center - backLegPosRes) * scale);
    m_frontLeg.transformation().setOrigin((center - frontLegPosRes) * scale);
    m_tail.transformation().setOrigin((center - tailPosRes) * scale);
    m_leftEar.transformation().setOrigin((center - leftEarPosRes) * scale);
    m_rightEar.transformation().setOrigin((center - rightEarPosRes) * scale);
    m_leftEye.transformation().setOrigin((center - leftEyePosRes) * scale);
    m_rightEye.transformation().setOrigin((center - rightEyePosRes) * scale);
    m_scarf.transformation().setOrigin((center - scarfPosRes) * scale);
    m_scarfTail.transformation().setOrigin((center - scarfTailPosRes) * scale);
    m_mouth.transformation().setOrigin((center - mouthPosRes) * scale);

    m_body.transformation().setRotation(angle);
    m_head.transformation().setRotation(angle);
    m_backLeg.transformation().setRotation(angle);
    m_frontLeg.transformation().setRotation(angle);
    m_tail.transformation().setRotation(angle);
    m_leftEar.transformation().setRotation(angle);
    m_rightEar.transformation().setRotation(angle);
    m_leftEye.transformation().setRotation(angle);
    m_rightEye.transformation().setRotation(angle);
    m_scarf.transformation().setRotation(angle);
    m_scarfTail.transformation().setRotation(angle);
    m_mouth.transformation().setRotation(angle);
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
