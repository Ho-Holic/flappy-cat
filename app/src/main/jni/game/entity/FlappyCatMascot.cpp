#include "FlappyCatMascot.hpp"

FlappyCatMascot::FlappyCatMascot(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatMascot>(gameConstants)
    , m_body()
    , m_backLeg()
    , m_frontLeg()
    , mTail()
    , mScarf()
    , mScarfTail()
    , m_head()
    , m_leftEar()
    , mRightEar()
    , m_leftEye()
    , mRightEye()
    , m_mouth()
{
    //
}

void FlappyCatMascot::drawOn(const Window& window) const
{
    window.draw(m_body);
    window.draw(m_backLeg);
    window.draw(m_frontLeg);
    window.draw(mTail);
    window.draw(mScarf);
    window.draw(mScarfTail);
    window.draw(m_head);
    window.draw(m_leftEar);
    window.draw(mRightEar);
    window.draw(m_leftEye);
    window.draw(mRightEye);
    window.draw(m_mouth);
}

void FlappyCatMascot::syncChildren()
{
    const Position& pos = position();
    float angle = rotation();

    Position referenceSize(2000.f, 2000.f); // must be equal, 2000x2000 square

    Position scale = size() / referenceSize;

    // relation between parts
    Position bodyPos = Position(0.f, 0.f);

    Position bodySize(1000.f, 500.f);
    Position headPos(660.f, 340.f);
    Position headSize(570.f, 440.f);
    Position backLegPos(0.f, -375.f);
    Position frontLegPos(625.f, 0.f);
    Position legAndTailSize(150.f, 500.f);
    Position tailPos(0.f, 250.f);
    Position earSize(200.f, 375.f);
    Position leftEarPos(0.f, headSize.y()); // 0.f, 440.f
    Position rightEarPos(headSize.x() - earSize.x(), 0.f); // 360.f, 0
    Position eyeSize(145.f, 145.f);
    Position leftEyePos(80.f, 200.f);
    Position rightEyePos(300.f, 0.f);
    Position scarfSize(750.f, 210.f);
    Position scarfPos(400.f, 210.f);
    Position scarfTailSize(150.f, 315.f);
    Position scarfTailPos(75.f, -148.f);
    Position mouthSize(56.f, 36.f);
    Position mouthPos(280.f, 96.f);

    // move
    // TODO: later remove additional Res variables
    Position bodyPosRes = bodyPos;
    Position headPosRes = bodyPos + headPos;
    Position backLegPosRes = bodyPos + backLegPos;
    Position frontLegPosRes = bodyPos + backLegPos + frontLegPos;
    Position tailPosRes = bodyPos + tailPos;
    Position leftEarPosRes = bodyPos + headPos + leftEarPos;
    Position rightEarPosRes = bodyPos + headPos + leftEarPos + rightEarPos;

    Position leftEyePosRes = bodyPos + headPos + leftEyePos;
    Position rightEyePosRes = bodyPos + headPos + leftEyePos + rightEyePos;

    Position scarfPosRes = bodyPos + scarfPos;
    Position scarfTailPosRes = bodyPos + scarfPos + scarfTailPos;
    Position mouthPosRes = bodyPos + headPos + mouthPos;

    // place objects

    m_body.transformation().setPosition(pos + bodyPosRes * scale);
    m_head.transformation().setPosition(pos + headPosRes * scale);
    m_backLeg.transformation().setPosition(pos + backLegPosRes * scale);
    m_frontLeg.transformation().setPosition(pos + frontLegPosRes * scale);
    mTail.transformation().setPosition(pos + tailPosRes * scale);
    m_leftEar.transformation().setPosition(pos + leftEarPosRes * scale);
    mRightEar.transformation().setPosition(pos + rightEarPosRes * scale);
    m_leftEye.transformation().setPosition(pos + leftEyePosRes * scale);
    mRightEye.transformation().setPosition(pos + rightEyePosRes * scale);
    mScarf.transformation().setPosition(pos + scarfPosRes * scale);
    mScarfTail.transformation().setPosition(pos + scarfTailPosRes * scale);
    m_mouth.transformation().setPosition(pos + mouthPosRes * scale);

    // resize objects
    m_body.geometry().resize(bodySize * scale);
    m_head.geometry().resize(headSize * scale);
    m_backLeg.geometry().resize(legAndTailSize * scale);
    m_frontLeg.geometry().resize(legAndTailSize * scale);
    mTail.geometry().resize(legAndTailSize * scale);
    m_leftEar.geometry().resize(earSize * scale);
    mRightEar.geometry().resize(earSize * scale);
    m_leftEye.geometry().resize(eyeSize * scale);
    mRightEye.geometry().resize(eyeSize * scale);
    mScarf.geometry().resize(scarfSize * scale);
    mScarfTail.geometry().resize(scarfTailSize * scale);
    m_mouth.geometry().resize(mouthSize * scale);

    // rotate

    Position center(bodySize.x() / 2.f, bodySize.y() / 2.f);

    m_body.transformation().setOrigin((center - bodyPosRes) * scale);
    m_head.transformation().setOrigin((center - headPosRes) * scale);
    m_backLeg.transformation().setOrigin((center - backLegPosRes) * scale);
    m_frontLeg.transformation().setOrigin((center - frontLegPosRes) * scale);
    mTail.transformation().setOrigin((center - tailPosRes) * scale);
    m_leftEar.transformation().setOrigin((center - leftEarPosRes) * scale);
    mRightEar.transformation().setOrigin((center - rightEarPosRes) * scale);
    m_leftEye.transformation().setOrigin((center - leftEyePosRes) * scale);
    mRightEye.transformation().setOrigin((center - rightEyePosRes) * scale);
    mScarf.transformation().setOrigin((center - scarfPosRes) * scale);
    mScarfTail.transformation().setOrigin((center - scarfTailPosRes) * scale);
    m_mouth.transformation().setOrigin((center - mouthPosRes) * scale);

    m_body.transformation().setRotation(angle);
    m_head.transformation().setRotation(angle);
    m_backLeg.transformation().setRotation(angle);
    m_frontLeg.transformation().setRotation(angle);
    mTail.transformation().setRotation(angle);
    m_leftEar.transformation().setRotation(angle);
    mRightEar.transformation().setRotation(angle);
    m_leftEye.transformation().setRotation(angle);
    mRightEye.transformation().setRotation(angle);
    mScarf.transformation().setRotation(angle);
    mScarfTail.transformation().setRotation(angle);
    m_mouth.transformation().setRotation(angle);
}

void FlappyCatMascot::setColor(const Color& bodyColor,
    const Color& scarfColor,
    const Color& mouthColor)
{
    m_body.setColor(bodyColor);
    m_backLeg.setColor(bodyColor);
    m_frontLeg.setColor(bodyColor);
    mTail.setColor(bodyColor);
    m_head.setColor(bodyColor);
    m_leftEar.setColor(bodyColor);
    mRightEar.setColor(bodyColor);

    mScarf.setColor(scarfColor);
    mScarfTail.setColor(scarfColor);
    m_leftEye.setColor(scarfColor);
    mRightEye.setColor(scarfColor);

    m_mouth.setColor(mouthColor);
}

std::vector<std::shared_ptr<Geometry>> FlappyCatMascot::duplicateParts() const
{
    std::vector<std::shared_ptr<Geometry>> parts;
    //parts.push_back(std::make_shared<RectangleShape>(m_body));
    return parts;
}
