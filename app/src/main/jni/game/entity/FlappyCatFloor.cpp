#include "FlappyCatFloor.hpp"

FlappyCatFloor::FlappyCatFloor(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatFloor>(gameConstants)
    , m_organicSurfaceSize()
    , m_spikesSize()
    , m_floor()
    , m_floorSpikes(gameConstants)
    , m_backgroundDirt()
{
    //
}

void FlappyCatFloor::initialize()
{
    m_floorSpikes.initialize();
}

void FlappyCatFloor::syncChildren()
{
    // floor for collide
    m_floor.transformation().setPosition(position());
    m_floor.geometry().resize(vec2(size().x, m_organicSurfaceSize.y));

    // spikes for movement effect
    m_floorSpikes.moveTo(position() - vec2(0.f, m_spikesSize.y));

    m_floorSpikes.setLinkSize(m_spikesSize);
    m_floorSpikes.setOffsetBetweenLinks(m_spikesSize);

    m_floorSpikes.resize(vec2(size().x, 0.f));

    // dirt under floor
    m_backgroundDirt.transformation().setPosition(position() - vec2(0.f, size().y));
    m_backgroundDirt.geometry().resize(vec2(size().x, size().y));
}

void FlappyCatFloor::drawOn(const Window& window) const
{
    m_backgroundDirt.render().drawOn(window, window.view());
    m_floorSpikes.drawOn(window);
    m_floor.render().drawOn(window, window.view());
}

void FlappyCatFloor::update(const FrameDuration& time)
{
    FlappyCatStateNode<FlappyCatFloor>::update(time);
    m_floorSpikes.update(time);
}

void FlappyCatFloor::reset()
{
    FlappyCatStateNode<FlappyCatFloor>::reset();
    m_floorSpikes.reset();
}

const RectangleShape& FlappyCatFloor::boundingBox() const
{
    return m_floor;
}

void FlappyCatFloor::setColor(const Color& floorColor, const Color& dirtColor)
{
    m_floor.setColor(floorColor);

    m_floorSpikes.foreachLink(
        [&floorColor](FlappyCatSpike& spike) {
            spike.setColor(floorColor);
        });

    m_backgroundDirt.setColor(dirtColor);
}

void FlappyCatFloor::setMovementDisplacement(const vec2& movementDisplacement)
{
    m_floorSpikes.setMovementDisplacement(movementDisplacement);
}

void FlappyCatFloor::setDecorationSizes(const vec2& surfaceSize,
    const vec2& spikesSize)
{
    m_organicSurfaceSize = surfaceSize;
    m_spikesSize = spikesSize;

    syncChildren();
}
