#ifndef FLAPPY_CAT_FLAPPYCATCHAIN_H
#define FLAPPY_CAT_FLAPPYCATCHAIN_H

// self
#include <core/Position.h>
#include <core/Color.h>
#include <core/Clock.h>
#include <style/Guidelines.h>
#include <android/AndroidWindow.h>
#include "Log.h"

// stl
#include <vector>
#include <cmath>

template <typename Link>
class FlappyCatChain {
private:
  DISABLE_COPY(FlappyCatChain)

public:
  using Modifier = std::function<void(Link&)>;

public:
  FlappyCatChain();

public:
  void initialize();
  void reset();
  void update(const FrameDuration& time);
  void drawOn(const AndroidWindow& window) const;
  void setPosition(const Position& position);
  void setSize(const Position& size);
  void setLinkSize(const Position& linkSize);
  void setColor(const Color& color);
  void setMovementDisplacement(const Position& movementDisplacement);
  void setResetModifier(const Modifier& modifier);
  void setUpdateModifier(const Modifier& modifier);
  void setWrapAroundModifier(const Modifier& modifier);


private:
  Position mPosition;
  Position mSize;
  Position mLinkSize;
  Position mMovementDisplacement;
  Color mFillColor;
  std::vector<Link> mLinks;
  Modifier mResetModifier;
  Modifier mUpdateModifier;
  Modifier mWrapAroundModifier;
};

// implementation

template <typename Link>
FlappyCatChain<Link>::FlappyCatChain()
: mPosition(Position(0.f, 0.f))
, mSize(Position(0.f, 0.f))
, mLinkSize(Position(0.f, 0.f))
, mMovementDisplacement(Position(0.f, 0.f))
, mFillColor()
, mLinks()
, mResetModifier([](Link&){})
, mUpdateModifier([](Link&){})
, mWrapAroundModifier([](Link&){}){
  //
}

template <typename Link>
void FlappyCatChain<Link>::initialize() {

  // TODO: parametrize reserve function
  mLinks.reserve(120);

  std::size_t linkCount = static_cast<std::size_t>(mSize.x() / mLinkSize.x());

  for (std::size_t i = 0; i < linkCount;  ++i) {

    mLinks.emplace_back(mPosition, mLinkSize);
  }
}

template <typename Link>
void FlappyCatChain<Link>::reset() {

  for (std::size_t i = 0; i < mLinks.size(); ++i) {

    Position pos(mPosition.x() - mSize.x() + i * 2.f * mLinkSize.x(), mPosition.y());

    mLinks[i].moveTo(pos);
    mLinks[i].resize(mLinkSize);
    mLinks[i].setColor(mFillColor);

    REQUIRE(TAG, mResetModifier != nullptr, "Reset modifier must be not null");
    mResetModifier(mLinks[i]);
  }
}

template <typename Link>
void FlappyCatChain<Link>::update(const FrameDuration& time) {

  for (size_t i = 0; i < mLinks.size(); ++i) {

    mLinks[i].moveBy(mMovementDisplacement);
    mLinks[i].update(time);

    REQUIRE(TAG, mUpdateModifier != nullptr, "Update modifier must be not null");
    mUpdateModifier(mLinks[i]);

    Position p = mLinks[i].position();

    if (p.x() < -mSize.x()) {

      mLinks[i].moveTo(Position(p.x() + mSize.x() * 2.f, p.y()));

      REQUIRE(TAG, mWrapAroundModifier != nullptr, "WrapAround modifier must be not null");
      mWrapAroundModifier(mLinks[i]);
    }
  }

}

template <typename Link>
void FlappyCatChain<Link>::drawOn(const AndroidWindow& window) const {

  for (const Link& link : mLinks) {
    link.drawOn(window);
  }
}

template <typename Link>
void FlappyCatChain<Link>::setResetModifier(const Modifier& modifier) {

  mResetModifier = modifier;
}

template <typename Link>
void FlappyCatChain<Link>::setUpdateModifier(const Modifier& modifier) {

  mUpdateModifier = modifier;
}

template <typename Link>
void FlappyCatChain<Link>::setWrapAroundModifier(const Modifier& modifier) {

  mWrapAroundModifier = modifier;
}

template <typename Link>
void FlappyCatChain<Link>::setColor(const Color& color) {

  mFillColor = color;
}

template <typename Link>
void FlappyCatChain<Link>::setPosition(const Position& position) {

  mPosition = position;
}

template <typename Link>
void FlappyCatChain<Link>::setSize(const Position& size) {

  mSize = size;
}

template <typename Link>
void FlappyCatChain<Link>::setLinkSize(const Position& linkSize) {

  mLinkSize = linkSize;
}

template <typename Link>
void FlappyCatChain<Link>::setMovementDisplacement(const Position& movementDisplacement) {

  mMovementDisplacement = movementDisplacement;
}


#endif //FLAPPY_CAT_FLAPPYCATCHAIN_H
