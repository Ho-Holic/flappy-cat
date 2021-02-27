#pragma once

#include "entity/FlappyCatStateNode.hpp"
#include <cmath>
#include <core/Clock.hpp>
#include <core/Color.hpp>
#include <core/Log.hpp>
#include <core/Position.hpp>
#include <core/Window.hpp>
#include <style/Guidelines.hpp>
#include <vector>

template <typename Link>
class FlappyCatChain : public FlappyCatStateNode<FlappyCatChain<Link>> {
private:
    FlappyCatChain(const FlappyCatChain&) = delete;
    FlappyCatChain& operator=(const FlappyCatChain&) = delete;

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

public:
    void setLinkSize(const Position& linkSize);
    void setOffsetBetweenLinks(const Position& offset);
    void setStartOffset(const Position& offset);
    void setMovementDisplacement(const Position& movementDisplacement);
    void setWrapAroundModifier(const modifier_type& modifier);

public:
    template <typename Fn>
    void foreachLink(const Fn& modifier);

private:
    float chainLength() const;
    bool isWarpNeeded(const Position& point) const;
    Position section() const;

private:
    Position mLinkSize;
    Position mOffsetBetweenLinks;
    Position mStartOffset;
    Position mMovementDisplacement;
    std::vector<entity_type> mLinks;
    modifier_type mWrapAroundModifier;
};

// implementation

template <typename Link>
FlappyCatChain<Link>::FlappyCatChain(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatChain<Link>>(gameConstants)
    , mLinkSize()
    , mOffsetBetweenLinks(0.f, 0.f)
    , mStartOffset(0.f, 0.f)
    , mMovementDisplacement(0.f, 0.f)
    , mLinks()
    , mWrapAroundModifier([](entity_type&) {})
{
    static_assert(std::is_base_of<FlappyCatEntity, Link>::value, "Must be derived from Entity");
}

template <typename Link>
float FlappyCatChain<Link>::chainLength() const
{
    /*
   * TODO: Math functions does not work properly
   *
   * We don't have proper cmath header, replace with code below in NDK r15 (May 27 , 2017)
   * replace code with:
   *
   *     return std::round(mSize.x() / section().x()) * section().x();
   *
   * Read more about problem:
   * https://github.com/android-ndk/ndk/milestone/7
   * https://github.com/android-ndk/ndk/issues/82
   * https://code.google.com/p/android/issues/detail?id=82734
   */

    return static_cast<size_t>(this->size().x() / section().x()) * section().x();
}

template <typename Link>
Position FlappyCatChain<Link>::section() const
{
    return mLinkSize + mOffsetBetweenLinks;
}

template <typename Link>
bool FlappyCatChain<Link>::isWarpNeeded(const Position& point) const
{
    return point.x() < this->position().x();
}

template <typename Link>
void FlappyCatChain<Link>::initialize()
{
    /*
   * TODO: Write code for better offset usage
   *
   * If mOffsetBetweenLinks is set before `initialize()` then incorrect behaviour
   * would be observed when one would call setOffsetBetweenLinks()
   */
    std::size_t linkCount = static_cast<std::size_t>(chainLength() / section().x());

    CAUTION("If all of a sudden no object appears on the screen, please pass"
            "some hardcoded value e.g 'mLinks.reserve(120)' and check if bug appears"
            "this appears if 'emplace_back' is not implemented properly");

    mLinks.reserve(linkCount);

    for (std::size_t i = 0; i < linkCount; ++i) {

        mLinks.emplace_back(this->gameConstants());
    }
}

template <typename Link>
void FlappyCatChain<Link>::reset()
{
    FlappyCatStateNode<FlappyCatChain<Link>>::reset();

    for (std::size_t i = 0; i < mLinks.size(); ++i) {

        // TODO: replace with Position pos(position + Position(i * section().x(), 0.f));
        Position pos(this->position().x() + i * section().x(), this->position().y());

        mLinks[i].moveTo(pos + mStartOffset); // shift off-screen if needed by mStartOffset
        mLinks[i].resize(mLinkSize);

        mLinks[i].reset();
    }
}

template <typename Link>
void FlappyCatChain<Link>::update(const FrameDuration& time)
{
    for (Link& link : mLinks) {

        link.moveBy(mMovementDisplacement);
        link.update(time);

        Position p = link.position();

        if (isWarpNeeded(p)) {

            // TODO: If 'p.x()' bigger then '2.f * chainLength' then wrap fails, need a loop
            link.moveTo(Position(p.x() + chainLength(), p.y()));

            REQUIRE(TAG, mWrapAroundModifier != nullptr, "WrapAround modifier must be not null");
            mWrapAroundModifier(link);
        }
    }
}

template <typename Link>
void FlappyCatChain<Link>::drawOn(const Window& window) const
{
    for (const entity_type& link : mLinks) {
        link.drawOn(window);
    }
}

template <typename Link>
void FlappyCatChain<Link>::setWrapAroundModifier(const modifier_type& modifier)
{
    mWrapAroundModifier = modifier;
}

template <typename Link>
void FlappyCatChain<Link>::setLinkSize(const Position& linkSize)
{
    mLinkSize = linkSize;
}

template <typename Link>
void FlappyCatChain<Link>::setMovementDisplacement(const Position& movementDisplacement)
{
    mMovementDisplacement = movementDisplacement;
}

template <typename Link>
void FlappyCatChain<Link>::setOffsetBetweenLinks(const Position& offset)
{
    mOffsetBetweenLinks = offset;
}

template <typename Link>
void FlappyCatChain<Link>::setStartOffset(const Position& offset)
{
    mStartOffset = offset;
}

template <typename Link>
template <typename Fn>
void FlappyCatChain<Link>::foreachLink(const Fn& modifier)
{
    for (Link& link : mLinks) {
        modifier(link);
    }
}
