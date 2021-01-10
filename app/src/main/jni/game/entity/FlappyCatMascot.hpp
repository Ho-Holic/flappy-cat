#ifndef FLAPPY_CAT_FLAPPYCATMASCOT_H
#define FLAPPY_CAT_FLAPPYCATMASCOT_H

// engine
#include <prototype/RectangleShape.h>
#include <prototype/TriangleShape.h>

// stl
#include <memory>

// game
#include "FlappyCatEntity.h"

class FlappyCatMascot : public FlappyCatEntity {
public:
  FlappyCatMascot(const FlappyCatGameConstants& gameConstants);

public:
  virtual void drawOn(const Window& window) const override;

public:
  void setColor(const Color& bodyColor,
                const Color& scarfColor,
                const Color& mouthColor);
  std::vector<std::shared_ptr<Geometry>> duplicateParts() const;


private:
  virtual void syncChildren() override;

private:

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
