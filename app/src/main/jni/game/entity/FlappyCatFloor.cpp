#include "FlappyCatFloor.hpp"

FlappyCatFloor::FlappyCatFloor(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatFloor>(gameConstants)
    , mOrganicSurfaceSize()
    , mSpikesSize()
    , mFloor()
    , mFloorSpikes(gameConstants)
    , m_backgroundDirt()
{
    //
}

void FlappyCatFloor::initialize()
{
    mFloorSpikes.initialize();
}

void FlappyCatFloor::syncChildren()
{
    // floor for collide
    mFloor.transformation().setPosition(position());
    mFloor.geometry().resize(Position(size().x(), mOrganicSurfaceSize.y()));

    // spikes for movement effect
    mFloorSpikes.moveTo(position() - Position(0.f, mSpikesSize.y()));

    mFloorSpikes.setLinkSize(mSpikesSize);
    mFloorSpikes.setOffsetBetweenLinks(mSpikesSize);

    mFloorSpikes.resize(Position(size().x(), 0.f));

    // dirt under floor
    m_backgroundDirt.transformation().setPosition(position() - Position(0.f, size().y()));
    m_backgroundDirt.geometry().resize(Position(size().x(), size().y()));
}

void FlappyCatFloor::drawOn(const Window& window) const
{
    window.draw(m_backgroundDirt);
    mFloorSpikes.drawOn(window);
    window.draw(mFloor);
}

void FlappyCatFloor::update(const FrameDuration& time)
{
    FlappyCatStateNode<FlappyCatFloor>::update(time);
    mFloorSpikes.update(time);
}

void FlappyCatFloor::reset()
{
    FlappyCatStateNode<FlappyCatFloor>::reset();
    mFloorSpikes.reset();
}

const RectangleShape& FlappyCatFloor::boundingBox() const
{
    return mFloor;
}

void FlappyCatFloor::setColor(const Color& floorColor, const Color& dirtColor)
{
    mFloor.setColor(floorColor);

    mFloorSpikes.foreachLink(
        [&floorColor](FlappyCatSpike& spike) {
            spike.setColor(floorColor);
        });

    m_backgroundDirt.setColor(dirtColor);
}

void FlappyCatFloor::setMovementDisplacement(const Position& movementDisplacement)
{
    mFloorSpikes.setMovementDisplacement(movementDisplacement);
}

void FlappyCatFloor::setDecorationSizes(const Position& surfaceSize,
    const Position& spikesSize)
{
    mOrganicSurfaceSize = surfaceSize;
    mSpikesSize = spikesSize;

    syncChildren();
}
