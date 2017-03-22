#ifndef FLAPPY_CAT_FLAPPYCATMASCOT_H
#define FLAPPY_CAT_FLAPPYCATMASCOT_H

// engine
#include <prototype/RectangleShape.h>
#include <prototype/TriangleShape.h>

// self
#include "FlappyCatEntity.h"

class FlappyCatMascot : public FlappyCatEntity {
public:
  FlappyCatMascot(const FlappyCatGameConstants& gameConstants);

public:
  virtual void drawOn(const Window& window) const override;
  virtual const Position& position() const override;
  virtual void moveTo(const Position& position) override;
  virtual void resize(const Position& size) override;

public:
  void setColor(const Color& bodyColor,
                const Color& eyesColor,
                const Color& mouthColor);

private:
  void syncFigure();

private:
  Position mPosition;
  Position mSize;
  RectangleShape mBody;
  RectangleShape mBackLeg;
  RectangleShape mFrontLeg;
  RectangleShape mTail;
  RectangleShape mScarf;
  RectangleShape mScarfTail;
  RectangleShape mHead;
  TriangleShape  mLeftEar;
  TriangleShape  mRightEar;
  RectangleShape mLeftEye;
  RectangleShape mRightEye;
  RectangleShape mMouth;
};


#endif //FLAPPY_CAT_FLAPPYCATMASCOT_H
