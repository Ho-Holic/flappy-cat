// game
#include "FlappyCatMascot.h"

FlappyCatMascot::FlappyCatMascot(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mPosition(0.f, 0.f)
, mSize()
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

const Position& FlappyCatMascot::position() const {

  return mPosition;
}

void FlappyCatMascot::moveTo(const Position& position) {

  mPosition = position;

  syncFigure();
}

void FlappyCatMascot::resize(const Position& size) {

  mSize = size;

  syncFigure();
}

void FlappyCatMascot::syncFigure() {

  Position referenceSize(2000.f, 2000.f);

  Position scale = mSize / referenceSize;
  
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

  // place objects

  mBody     .transformation().setPosition(mPosition + (bodyPos) * scale);
  mHead     .transformation().setPosition(mPosition + (bodyPos + headPos) * scale);
  mBackLeg  .transformation().setPosition(mPosition + (bodyPos + backLegPos) * scale);
  mFrontLeg .transformation().setPosition(mPosition + (bodyPos + backLegPos + frontLegPos) * scale);
  mTail     .transformation().setPosition(mPosition + (bodyPos + tailPos) * scale);
  mLeftEar  .transformation().setPosition(mPosition + (bodyPos + headPos + leftEarPos) * scale);
  mRightEar .transformation().setPosition(mPosition + (bodyPos + headPos + leftEarPos + rightEarPos)
                                                      * scale);
  mLeftEye  .transformation().setPosition(mPosition + (bodyPos + headPos + leftEyePos) * scale);
  mRightEye .transformation().setPosition(mPosition + (bodyPos + headPos + leftEyePos + rightEyePos)
                                                      * scale);
  mScarf    .transformation().setPosition(mPosition + (bodyPos + scarfPos) * scale);
  mScarfTail.transformation().setPosition(mPosition + (bodyPos + scarfPos + scarfTailPos) * scale);
  mMouth    .transformation().setPosition(mPosition + (bodyPos + headPos + mouthPos) * scale);
  
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

  // TODO: remove code below
//  // --- tmp v
//  static float p = 0;
//
//  mBody     .transformation().setRotation(p);
//  mHead     .transformation().setRotation(p);
//  mBackLeg  .transformation().setRotation(p);
//  mFrontLeg .transformation().setRotation(p);
//  mTail     .transformation().setRotation(p);
//  mLeftEar  .transformation().setRotation(p);
//  mRightEar .transformation().setRotation(p);
//  mLeftEye  .transformation().setRotation(p);
//  mRightEye .transformation().setRotation(p);
//  mScarf    .transformation().setRotation(p);
//  mScarfTail.transformation().setRotation(p);
//  mMouth    .transformation().setRotation(p);
//
//  p += 0.1;
//
//  if (p > 360.f) p = 0.f;
//  // --- tmp ^

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
