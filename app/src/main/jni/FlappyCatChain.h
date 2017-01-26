#ifndef FLAPPY_CAT_FLAPPYCATCHAIN_H
#define FLAPPY_CAT_FLAPPYCATCHAIN_H

// self
#include <core/Position.h>
#include <core/Color.h>
#include <core/Clock.h>
#include <style/Guidelines.h>
#include <android/AndroidWindow.h>

// stl
#include <vector>
#include <cmath>

template <typename Link>
class FlappyCatChain {
private:
  DISABLE_COPY(FlappyCatChain)

public:
  using modify_callback = std::function<void(Link&)>;

public:
  FlappyCatChain();

public:
  void initialize();
  void reset(modify_callback modify = nullptr);
  void update(const FrameDuration& time,
              modify_callback modify = nullptr,
              modify_callback wrapAround = nullptr);
  void drawOn(const AndroidWindow& window) const;
  void setPosition(const Position& position);
  void setSize(const Position& size);
  void setLinkSize(const Position& linkSize);
  void setColor(const Color& color);
  void setMovementDisplacement(const Position& movementDisplacement);


private:
  Position mPosition;
  Position mSize;
  Position mLinkSize;
  Position mMovementDisplacement;
  Color mFillColor;
  std::vector<Link> mLinks;
};

// implementation

template <typename Link>
FlappyCatChain<Link>::FlappyCatChain()
: mPosition(Position(0.f, 0.f))
, mSize(Position(0.f, 0.f))
, mLinkSize(Position(0.f, 0.f))
, mMovementDisplacement(Position(0.f, 0.f))
, mFillColor()
, mLinks() {
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
void FlappyCatChain<Link>::reset(modify_callback modify) {

  for (std::size_t i = 0; i < mLinks.size(); ++i) {

    Position pos(mPosition.x() - mSize.x() + i * 2.f * mLinkSize.x(), mPosition.y());

    mLinks[i].transformation().setPosition(pos);
    mLinks[i].geometry().resize(mLinkSize);
    mLinks[i].setColor(mFillColor);
    modify(mLinks[i]);
  }
}

template <typename Link>
void FlappyCatChain<Link>::update(const FrameDuration& time,
                                  modify_callback modify,
                                  modify_callback wrapAround) {

  for (size_t i = 0; i < mLinks.size(); ++i) {

    mLinks[i].transformation().move(mMovementDisplacement);
    modify(mLinks[i]);

    Position p = mLinks[i].transformation().position();

    if (p.x() < -mSize.x()) {

      mLinks[i].transformation().setPosition(Position(p.x() + mSize.x() * 2.f, p.y()));
      wrapAround(mLinks[i]);
    }
  }

}

template <typename Link>
void FlappyCatChain<Link>::drawOn(const AndroidWindow& window) const {

  for (const Link& link : mLinks) {
    window.draw(link);
  }
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
