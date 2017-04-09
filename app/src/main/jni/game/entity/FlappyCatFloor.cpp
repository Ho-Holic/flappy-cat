// game
#include "FlappyCatFloor.h"

FlappyCatFloor::FlappyCatFloor(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mPosition()
, mSize()
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
  mFloor.transformation().setPosition(mPosition);
  mFloor.geometry().resize(Position(mSize.x(), mOrganicSurfaceSize.y()));

  // spikes for movement effect
  mFloorSpikes.moveTo(Position(mPosition.x(), mPosition.y() - mSpikesSize.y()));

  mFloorSpikes.setLinkSize(mSpikesSize);
  mFloorSpikes.setOffsetBetweenLinks(mSpikesSize);

  mFloorSpikes.resize(Position(mSize.x(), 0.f));

  // dirt under floor
  mBackgroundDirt.transformation().setPosition(Position(mPosition.x(), mPosition.y() - mSize.y()));
  mBackgroundDirt.geometry().resize(Position(mSize.x(), mSize.y()));
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

void FlappyCatFloor::moveTo(const Position& position) {

  mPosition = position;

  syncChildren();
}

void FlappyCatFloor::resize(const Position& size) {

  mSize = size;

  syncChildren();
}

const Position& FlappyCatFloor::position() const {

  return mPosition;
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
