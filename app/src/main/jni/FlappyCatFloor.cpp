// self
#include "FlappyCatFloor.h"

FlappyCatFloor::FlappyCatFloor(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mPosition()
, mSize()
, mFloor()
, mFloorSpikes(gameConstants)
, mBackgroundDirt()
, mResetModifier([](entity_type&){}) {
  //
}

void FlappyCatFloor::initialize() {

  mFloorSpikes.initialize();
}

void FlappyCatFloor::syncChildren() {


  // floor for collide
  Position::value_type floorHeight = mSize.y() * 0.1f; // 10% of height
  Position::value_type spikeHeight = mSize.y() * 0.125f;

  mFloor.transformation().setPosition(mPosition);
  mFloor.geometry().resize(Position(mSize.x(), floorHeight));

  // spikes for movement effect
  mFloorSpikes.moveTo(Position(mPosition.x(), mPosition.y() - spikeHeight));

  mFloorSpikes.setLinkSize(Position(spikeHeight, spikeHeight));
  mFloorSpikes.setOffsetBetweenLinks(Position(spikeHeight, spikeHeight));

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
