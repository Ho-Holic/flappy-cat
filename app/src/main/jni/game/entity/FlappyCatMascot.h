#ifndef FLAPPY_CAT_FLAPPYCATMASCOT_H
#define FLAPPY_CAT_FLAPPYCATMASCOT_H

// engine
#include <prototype/RectangleShape.h>
#include <prototype/TriangleShape.h>

// game
#include "FlappyCatEntity.h"

class FlappyCatMascot : public FlappyCatEntity {
public:
  FlappyCatMascot(const FlappyCatGameConstants& gameConstants);

public:
  virtual void drawOn(const Window& window) const override;
  virtual const Position& position() const override;
  virtual void moveTo(const Position& position) override;
  virtual void resize(const Position& size) override;
  void rotate(Position::value_type angle) override;

public:
  void setColor(const Color& bodyColor,
                const Color& scarfColor,
                const Color& mouthColor);

private:
  void syncFigure();

private:
  Position mPosition;
  Position mSize;
  Position::value_type mAngle;

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
