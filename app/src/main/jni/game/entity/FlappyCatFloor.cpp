#include "FlappyCatFloor.hpp"

FlappyCatFloor::FlappyCatFloor(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatFloor>(gameConstants)
    , mOrganicSurfaceSize()
    , mSpikesSize()
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
    m_floor.geometry().resize(Position(size().x(), mOrganicSurfaceSize.y()));

    // spikes for movement effect
    m_floorSpikes.moveTo(position() - Position(0.f, mSpikesSize.y()));

    m_floorSpikes.setLinkSize(mSpikesSize);
    m_floorSpikes.setOffsetBetweenLinks(mSpikesSize);

    m_floorSpikes.resize(Position(size().x(), 0.f));

    // dirt under floor
    m_backgroundDirt.transformation().setPosition(position() - Position(0.f, size().y()));
    m_backgroundDirt.geometry().resize(Position(size().x(), size().y()));
}

void FlappyCatFloor::drawOn(const Window& window) const
{
    window.draw(m_backgroundDirt);
    m_floorSpikes.drawOn(window);
    window.draw(m_floor);
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

void FlappyCatFloor::setMovementDisplacement(const Position& movementDisplacement)
{
    m_floorSpikes.setMovementDisplacement(movementDisplacement);
}

void FlappyCatFloor::setDecorationSizes(const Position& surfaceSize,
    const Position& spikesSize)
{
    mOrganicSurfaceSize = surfaceSize;
    mSpikesSize = spikesSize;

    syncChildren();
}
