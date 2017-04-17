// game
#include "FlappyCatMascot.h"

FlappyCatMascot::FlappyCatMascot(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mBody()
, mBackLeg()
, mFrontLeg()
, mTail()
, mScarf()
, mScarfTail()
, mHead()
, mLeftEar()
, mRightEar()
, mLeftEye()
, mRightEye()
, mMouth() {
  //
}

void FlappyCatMascot::drawOn(const Window& window) const {

  window.draw(mBody);
  window.draw(mBackLeg);
  window.draw(mFrontLeg);
  window.draw(mTail);
  window.draw(mScarf);
  window.draw(mScarfTail);
  window.draw(mHead);
  window.draw(mLeftEar);
  window.draw(mRightEar);
  window.draw(mLeftEye);
  window.draw(mRightEye);
  window.draw(mMouth);
}

void FlappyCatMascot::syncChildren() {

  const Position& pos = position();
  Position::value_type angle = rotation();
  
  Position referenceSize(2000.f, 2000.f);

  Position scale = size() / referenceSize;
  
  // relation between parts
  Position bodyPos = Position(0.f, 0.f);

  Position bodySize      (1000.f, 500.f);
  Position headPos       (600.f, 375.f);
  Position headSize      (560.f, 440.f);
  Position backLegPos    (0.f, -375.f);
  Position frontLegPos   (625.f, 0.f);
  Position legAndTailSize(150.f, 500.f);
  Position tailPos       (0.f, 175.f);
  Position earSize       (200.f, 375.f);
  Position leftEarPos    (0.f, headSize.y()); // 0.f, 440.f
  Position rightEarPos   (headSize.x() - earSize.x(), 0.f); // 360.f, 0
  Position eyeSize       (140.f, 140.f);
  Position leftEyePos    (80.f, 220.f);
  Position rightEyePos   (300.f, 0.f);
  Position scarfSize     (750.f, 210.f);
  Position scarfPos      (340.f, 210.f);
  Position scarfTailSize (150.f, 315.f);
  Position scarfTailPos  (75.f,  -148.f);
  Position mouthSize     (56.f, 36.f);
  Position mouthPos      (280.f, 96.f);

  // move
  // TODO: later remove additional Res variables
  Position bodyPosRes      = bodyPos;
  Position headPosRes      = bodyPos + headPos;
  Position backLegPosRes   = bodyPos + backLegPos;
  Position frontLegPosRes  = bodyPos + backLegPos + frontLegPos;
  Position tailPosRes      = bodyPos + tailPos;
  Position leftEarPosRes   = bodyPos + headPos + leftEarPos;
  Position rightEarPosRes  = bodyPos + headPos + leftEarPos + rightEarPos;

  Position leftEyePosRes   = bodyPos + headPos + leftEyePos;
  Position rightEyePosRes  = bodyPos + headPos + leftEyePos + rightEyePos;

  Position scarfPosRes     = bodyPos + scarfPos;
  Position scarfTailPosRes = bodyPos + scarfPos + scarfTailPos;
  Position mouthPosRes     = bodyPos + headPos + mouthPos;



  // place objects

  mBody     .transformation().setPosition(pos + bodyPosRes * scale);
  mHead     .transformation().setPosition(pos + headPosRes * scale);
  mBackLeg  .transformation().setPosition(pos + backLegPosRes  * scale);
  mFrontLeg .transformation().setPosition(pos + frontLegPosRes * scale);
  mTail     .transformation().setPosition(pos + tailPosRes     * scale);
  mLeftEar  .transformation().setPosition(pos + leftEarPosRes  * scale);
  mRightEar .transformation().setPosition(pos + rightEarPosRes * scale);
  mLeftEye  .transformation().setPosition(pos + leftEyePosRes  * scale);
  mRightEye .transformation().setPosition(pos + rightEyePosRes * scale);
  mScarf    .transformation().setPosition(pos + scarfPosRes    * scale);
  mScarfTail.transformation().setPosition(pos + scarfTailPosRes * scale);
  mMouth    .transformation().setPosition(pos + mouthPosRes     * scale);
  
  // resize objects
  mBody     .geometry().resize(bodySize * scale);
  mHead     .geometry().resize(headSize * scale);
  mBackLeg  .geometry().resize(legAndTailSize * scale);
  mFrontLeg .geometry().resize(legAndTailSize * scale);
  mTail     .geometry().resize(legAndTailSize * scale);
  mLeftEar  .geometry().resize(earSize * scale);
  mRightEar .geometry().resize(earSize * scale);
  mLeftEye  .geometry().resize(eyeSize * scale);
  mRightEye .geometry().resize(eyeSize * scale);
  mScarf    .geometry().resize(scarfSize * scale);
  mScarfTail.geometry().resize(scarfTailSize * scale);
  mMouth    .geometry().resize(mouthSize * scale);
  
  // rotate

  Position center (bodySize.x() / 2.f, bodySize.y() / 2.f);

  mBody     .transformation().setOrigin((center - bodyPosRes) * scale);
  mHead     .transformation().setOrigin((center - headPosRes)* scale);
  mBackLeg  .transformation().setOrigin((center - backLegPosRes)* scale);
  mFrontLeg .transformation().setOrigin((center - frontLegPosRes)* scale);
  mTail     .transformation().setOrigin((center - tailPosRes)* scale);
  mLeftEar  .transformation().setOrigin((center - leftEarPosRes)* scale);
  mRightEar .transformation().setOrigin((center - rightEarPosRes)* scale);
  mLeftEye  .transformation().setOrigin((center - leftEyePosRes)* scale);
  mRightEye .transformation().setOrigin((center - rightEyePosRes)* scale);
  mScarf    .transformation().setOrigin((center - scarfPosRes)* scale);
  mScarfTail.transformation().setOrigin((center - scarfTailPosRes)* scale);
  mMouth    .transformation().setOrigin((center - mouthPosRes)* scale);

  mBody     .transformation().setRotation(angle);
  mHead     .transformation().setRotation(angle);
  mBackLeg  .transformation().setRotation(angle);
  mFrontLeg .transformation().setRotation(angle);
  mTail     .transformation().setRotation(angle);
  mLeftEar  .transformation().setRotation(angle);
  mRightEar .transformation().setRotation(angle);
  mLeftEye  .transformation().setRotation(angle);
  mRightEye .transformation().setRotation(angle);
  mScarf    .transformation().setRotation(angle);
  mScarfTail.transformation().setRotation(angle);
  mMouth    .transformation().setRotation(angle);

}



void FlappyCatMascot::setColor(const Color& bodyColor,
                               const Color& scarfColor,
                               const Color& mouthColor) {

  mBody.setColor(bodyColor);
  mBackLeg.setColor(bodyColor);
  mFrontLeg.setColor(bodyColor);
  mTail.setColor(bodyColor);
  mHead.setColor(bodyColor);
  mLeftEar.setColor(bodyColor);
  mRightEar.setColor(bodyColor);

  mScarf.setColor(scarfColor);
  mScarfTail.setColor(scarfColor);
  mLeftEye.setColor(scarfColor);
  mRightEye.setColor(scarfColor);

  mMouth.setColor(mouthColor);
}

