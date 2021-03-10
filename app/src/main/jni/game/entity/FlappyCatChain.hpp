#pragma once

#include "entity/FlappyCatStateNode.hpp"
#include <cmath>
#include <core/Clock.hpp>
#include <core/Color.hpp>
#include <core/Log.hpp>
#include <core/Window.hpp>
#include <math/vec2.hpp>
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
    void drawOn(const Window& window, const RenderContext& renderContext) const override;

public:
    void setLinkSize(const vec2& linkSize);
    void setOffsetBetweenLinks(const vec2& offset);
    void setStartOffset(const vec2& offset);
    void setMovementDisplacement(const vec2& movementDisplacement);
    void setWrapAroundModifier(const modifier_type& modifier);

public:
    template <typename Fn>
    void foreachLink(const Fn& modifier);

private:
    float chainLength() const;
    bool isWarpNeeded(const vec2& point) const;
    vec2 section() const;

private:
    vec2 m_linkSize;
    vec2 m_offsetBetweenLinks;
    vec2 m_startOffset;
    vec2 m_movementDisplacement;
    std::vector<entity_type> m_links;
    modifier_type m_wrapAroundModifier;
};

// implementation

template <typename Link>
FlappyCatChain<Link>::FlappyCatChain(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatChain<Link>>(gameConstants)
    , m_linkSize()
    , m_offsetBetweenLinks(0.f, 0.f)
    , m_startOffset(0.f, 0.f)
    , m_movementDisplacement(0.f, 0.f)
    , m_links()
    , m_wrapAroundModifier([](entity_type&) {})
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
   *     return std::round(m_size.x / section().x) * section().x;
   *
   * Read more about problem:
   * https://github.com/android-ndk/ndk/milestone/7
   * https://github.com/android-ndk/ndk/issues/82
   * https://code.google.com/p/android/issues/detail?id=82734
   */

    return static_cast<size_t>(this->size().x / section().x) * section().x;
}

template <typename Link>
vec2 FlappyCatChain<Link>::section() const
{
    return m_linkSize + m_offsetBetweenLinks;
}

template <typename Link>
bool FlappyCatChain<Link>::isWarpNeeded(const vec2& point) const
{
    return point.x < this->position().x;
}

template <typename Link>
void FlappyCatChain<Link>::initialize()
{
    /*
   * TODO: Write code for better offset usage
   *
   * If m_offsetBetweenLinks is set before `initialize()` then incorrect behaviour
   * would be observed when one would call setOffsetBetweenLinks()
   */
    std::size_t linkCount = static_cast<std::size_t>(chainLength() / section().x);

    CAUTION("If all of a sudden no object appears on the screen, please pass"
            "some hardcoded value e.g 'm_links.reserve(120)' and check if bug appears"
            "this appears if 'emplace_back' is not implemented properly");

    m_links.reserve(linkCount);

    for (std::size_t i = 0; i < linkCount; ++i) {

        m_links.emplace_back(this->gameConstants());
    }
}

template <typename Link>
void FlappyCatChain<Link>::reset()
{
    FlappyCatStateNode<FlappyCatChain<Link>>::reset();

    for (std::size_t i = 0; i < m_links.size(); ++i) {

        // TODO: replace with Position pos(position + Position(i * section().x, 0.f));
        vec2 pos(this->position().x + i * section().x, this->position().y);

        m_links[i].moveTo(pos + m_startOffset); // shift off-screen if needed by m_startOffset
        m_links[i].resize(m_linkSize);

        m_links[i].reset();
    }
}

template <typename Link>
void FlappyCatChain<Link>::update(const FrameDuration& time)
{
    for (Link& link : m_links) {

        link.moveBy(m_movementDisplacement);
        link.update(time);

        vec2 p = link.position();

        if (isWarpNeeded(p)) {

            // TODO: If 'p.x' bigger then '2.f * chainLength' then wrap fails, need a loop
            link.moveTo(vec2(p.x + chainLength(), p.y));

            REQUIRE(TAG, m_wrapAroundModifier != nullptr, "WrapAround modifier must be not null");
            m_wrapAroundModifier(link);
        }
    }
}

template <typename Link>
void FlappyCatChain<Link>::drawOn(const Window& window, const RenderContext& renderContext) const
{
    for (const entity_type& link : m_links) {
        link.drawOn(window, renderContext);
    }
}

template <typename Link>
void FlappyCatChain<Link>::setWrapAroundModifier(const modifier_type& modifier)
{
    m_wrapAroundModifier = modifier;
}

template <typename Link>
void FlappyCatChain<Link>::setLinkSize(const vec2& linkSize)
{
    m_linkSize = linkSize;
}

template <typename Link>
void FlappyCatChain<Link>::setMovementDisplacement(const vec2& movementDisplacement)
{
    m_movementDisplacement = movementDisplacement;
}

template <typename Link>
void FlappyCatChain<Link>::setOffsetBetweenLinks(const vec2& offset)
{
    m_offsetBetweenLinks = offset;
}

template <typename Link>
void FlappyCatChain<Link>::setStartOffset(const vec2& offset)
{
    m_startOffset = offset;
}

template <typename Link>
template <typename Fn>
void FlappyCatChain<Link>::foreachLink(const Fn& modifier)
{
    for (Link& link : m_links) {
        modifier(link);
    }
}
