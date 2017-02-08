#ifndef FLAPPY_CAT_FLAPPYCATCHAIN_H
#define FLAPPY_CAT_FLAPPYCATCHAIN_H

// engine
#include <core/Position.h>
#include <core/Color.h>
#include <core/Clock.h>
#include <core/Log.h>
#include <style/Guidelines.h>
#include <core/Window.h>

// stl
#include <vector>
#include <cmath>

template <typename Link>
class FlappyCatChain : public FlappyCatEntity {
private:
  DISABLE_COPY(FlappyCatChain)

public:
  using entity_type = Link;
  using modifier_type = std::function<void(entity_type&)>;

public:
  FlappyCatChain(const FlappyCatGameConstants& gameConstants);

public:
  void initialize() override;
  void reset() override;
  void update(const FrameDuration& time) override;
  void drawOn(const Window& window) const override;
  const Position& position() const override;
  void moveTo(const Position& position) override;
  void resize(const Position& size) override;
  void setColor(const Color& color) override;

public:
  void setLinkSize(const Position& linkSize);
  void setOffset(const Position& offset);
  void setMovementDisplacement(const Position& movementDisplacement);
  void setResetModifier(const modifier_type& modifier);
  void setUpdateModifier(const modifier_type& modifier);
  void setWrapAroundModifier(const modifier_type& modifier);

private:
  Position::position_type chainLength() const;
  bool isWarpNeeded(const Position& point) const;
  Position section() const;

private:
  Position mPosition;
  Position mSize;
  Position mLinkSize;
  Position mOffset;
  Position mMovementDisplacement;
  Color mFillColor;
  std::vector<entity_type> mLinks;
  modifier_type mResetModifier;
  modifier_type mUpdateModifier;
  modifier_type mWrapAroundModifier;
};

// implementation

template <typename Link>
FlappyCatChain<Link>::FlappyCatChain(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mPosition(Position(0.f, 0.f))
, mSize(Position(0.f, 0.f))
, mLinkSize(Position(0.f, 0.f))
, mOffset(Position(0.f, 0.f))
, mMovementDisplacement(Position(0.f, 0.f))
, mFillColor()
, mLinks()
, mResetModifier([](entity_type&){})
, mUpdateModifier([](entity_type&){})
, mWrapAroundModifier([](entity_type&){}){
  //
}

template <typename Link>
Position::position_type FlappyCatChain<Link>::chainLength() const {

  // TODO: We don't have proper 'cmath', replace with code below in NDK r15 (May 27 , 2017)
  // TODO: return std::round(mSize.x() / section().x()) * section().x();
  // https://github.com/android-ndk/ndk/milestone/7
  // https://github.com/android-ndk/ndk/issues/82
  // https://code.google.com/p/android/issues/detail?id=82734

  return static_cast<size_t>(mSize.x() / section().x()) * section().x();
}

template <typename Link>
Position FlappyCatChain<Link>::section() const {
  return mLinkSize + mOffset;
}

template <typename Link>
bool FlappyCatChain<Link>::isWarpNeeded(const Position& point) const {

  return point.x() < mPosition.x();
}

template <typename Link>
void FlappyCatChain<Link>::initialize() {

  // TODO: parametrize reserve function
  mLinks.reserve(120);

  std::size_t linkCount = static_cast<std::size_t>(chainLength() / mLinkSize.x());

  for (std::size_t i = 0; i < linkCount;  ++i) {

    mLinks.emplace_back(mPosition, mLinkSize, gameConstants());
  }
}

template <typename Link>
void FlappyCatChain<Link>::reset() {

  for (std::size_t i = 0; i < mLinks.size(); ++i) {

    Position pos(mPosition.x() + i * section().x(), mPosition.y());

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

    if (isWarpNeeded(p)) {

      // TODO: If 'p.x()' bigger then '2.f * chainLength' then wrap fails, need a loop
      mLinks[i].moveTo(Position(p.x() + chainLength(), p.y()));

      REQUIRE(TAG, mWrapAroundModifier != nullptr, "WrapAround modifier must be not null");
      mWrapAroundModifier(mLinks[i]);
    }
  }

}

template <typename Link>
void FlappyCatChain<Link>::drawOn(const Window& window) const {

  for (const entity_type& link : mLinks) {
    link.drawOn(window);
  }
}

template <typename Link>
void FlappyCatChain<Link>::setResetModifier(const modifier_type& modifier) {

  mResetModifier = modifier;
}

template <typename Link>
void FlappyCatChain<Link>::setUpdateModifier(const modifier_type& modifier) {

  mUpdateModifier = modifier;
}

template <typename Link>
void FlappyCatChain<Link>::setWrapAroundModifier(const modifier_type& modifier) {

  mWrapAroundModifier = modifier;
}

template <typename Link>
void FlappyCatChain<Link>::setColor(const Color& color) {

  mFillColor = color;
}

template <typename Link>
void FlappyCatChain<Link>::moveTo(const Position& position) {

  mPosition = position;
}

template <typename Link>
void FlappyCatChain<Link>::resize(const Position& size) {

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

template <typename Link>
void FlappyCatChain<Link>::setOffset(const Position& offset) {

  mOffset = offset;
}

template <typename Link>
const Position& FlappyCatChain<Link>::position() const {

  return mPosition;
}


#endif //FLAPPY_CAT_FLAPPYCATCHAIN_H
