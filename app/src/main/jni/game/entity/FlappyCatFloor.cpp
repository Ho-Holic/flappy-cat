// game
#include "FlappyCatFloor.hpp"

FlappyCatFloor::FlappyCatFloor(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mOrganicSurfaceSize()
, mSpikesSize()
, mFloor()
, mFloorSpikes(gameConstants)
, mBackgroundDirt()
, mResetModifier([](entity_type&){})
, mUpdateModifier([](entity_type&, const FrameDuration&){}) {
  //
}

void FlappyCatFloor::initialize() {

  mFloorSpikes.initialize();
}

void FlappyCatFloor::syncChildren() {

  // floor for collide
  mFloor.transformation().setPosition(position());
  mFloor.geometry().resize(Position(size().x(), mOrganicSurfaceSize.y()));

  // spikes for movement effect
  mFloorSpikes.moveTo(position() - Position(0.f, mSpikesSize.y()));

  mFloorSpikes.setLinkSize(mSpikesSize);
  mFloorSpikes.setOffsetBetweenLinks(mSpikesSize);

  mFloorSpikes.resize(Position(size().x(), 0.f));

  // dirt under floor
  mBackgroundDirt.transformation().setPosition(position() - Position(0.f, size().y()));
  mBackgroundDirt.geometry().resize(Position(size().x(), size().y()));
}


void FlappyCatFloor::drawOn(const Window& window) const {

  window.draw(mBackgroundDirt);
  mFloorSpikes.drawOn(window);
  window.draw(mFloor);
}

void FlappyCatFloor::update(const FrameDuration& time) {

  mFloorSpikes.update(time);
  mUpdateModifier(*this, time);
}

void FlappyCatFloor::reset() {

  mFloorSpikes.reset();
  mResetModifier(*this);
}

const RectangleShape& FlappyCatFloor::boundingBox() const {

  return mFloor;
}

void FlappyCatFloor::setColor(const Color& floorColor, const Color& dirtColor) {

  mFloor.setColor(floorColor);

  mFloorSpikes.foreachLink(
    [&floorColor](FlappyCatSpike& spike) {
      spike.setColor(floorColor);
    }
  );

  mBackgroundDirt.setColor(dirtColor);
}

void FlappyCatFloor::setResetModifier(const modifier_type& modifier) {

  mResetModifier = modifier;
}

void FlappyCatFloor::setMovementDisplacement(const Position& movementDisplacement) {

  mFloorSpikes.setMovementDisplacement(movementDisplacement);
}

void FlappyCatFloor::setUpdateModifier(const FlappyCatFloor::update_modifier_type& modifier) {

  mUpdateModifier = modifier;
}

void FlappyCatFloor::setDecorationSizes(const Position& surfaceSize,
                                        const Position& spikesSize) {
  mOrganicSurfaceSize = surfaceSize;
  mSpikesSize = spikesSize;

  syncChildren();
}
