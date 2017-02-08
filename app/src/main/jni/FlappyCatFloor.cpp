// self
#include "FlappyCatFloor.h"

FlappyCatFloor::FlappyCatFloor(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mPosition(0.f, 0.f)
, mSize(0.f, 0.f)
, mColor()
, mFloor(Position(0.f, 0.f), Position(0.f, 0.f))
, mFloorSpikes(gameConstants)
, mBackgroundDirt(Position(0.f, 0.f), Position(0.f, 0.f)){
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

void FlappyCatFloor::setColor(const Color& color) {

  mFloor.setColor(color);
  mFloorSpikes.setColor(color);
  mBackgroundDirt.setColor(gameConstants().colorScheme().dirt());
}

void FlappyCatFloor::reset() {

  mFloorSpikes.reset();
}

const Shape& FlappyCatFloor::boundingBox() const {

  return mFloor;
}



















