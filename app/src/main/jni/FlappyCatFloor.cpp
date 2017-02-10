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
  // floor
  mFloor.transformation().setPosition(mPosition);
  mFloor.geometry().resize(Position(mSize.x(), 20.f));

  // spikes (movement effect)
  mFloorSpikes.moveTo(Position(mPosition.x(), mPosition.y() - 25.f));
  mFloorSpikes.resize(Position(mSize.x(), 0.f));

  mFloorSpikes.setLinkSize(gameConstants().spikeSize());
  mFloorSpikes.setOffset(gameConstants().spikeSize());

  mFloorSpikes.setMovementDisplacement(Position(-10.f, 0.f));
  mFloorSpikes.initialize();

  // dirt under floor
  mBackgroundDirt.transformation().setPosition(Position(mPosition.x(), mPosition.y() - 100.f));
  mBackgroundDirt.geometry().resize(Position(mSize.x(), 100.f));
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
}

void FlappyCatFloor::resize(const Position& size) {

  mSize = size;
}

const Position& FlappyCatFloor::position() const {

  return mPosition;
}

void FlappyCatFloor::reset() {

  mFloorSpikes.reset();
  mResetModifier(*this);
}

const Shape& FlappyCatFloor::boundingBox() const {

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























