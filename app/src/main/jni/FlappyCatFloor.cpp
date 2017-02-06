// self
#include "FlappyCatFloor.h"

FlappyCatFloor::FlappyCatFloor()
: FlappyCatEntity()
, mPosition(0.f, 0.f)
, mSize(0.f, 0.f)
, mColor()
, mFloor(Position(0.f, 0.f), Position(0.f, 0.f))
, mFloorSpikes()
, mBackgroundDirt(Position(0.f, 0.f), Position(0.f, 0.f)){
  //
}

void FlappyCatFloor::initialize() {
  // floor
  mFloor.transformation().setPosition(mPosition);
  mFloor.geometry().resize(Position(mSize.x(), 20.f));

  // spikes (movement effect)
  mFloorSpikes.setPosition(Position(mPosition.x(), mPosition.y() - 25.f));
  mFloorSpikes.setSize(Position(mSize.x(), 0.f));

  mFloorSpikes.setLinkSize(Position(25.f, 25.f));
  mFloorSpikes.setOffset(Position(25.f, 25.f));
  //TODO: remove hardcoded size. mFloorSpikes.setLinkSize(mGameConstants.spikeSize());
  //TODO: remove hardcoded size. mFloorSpikes.setOffset(mGameConstants.spikeSize());

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
  mBackgroundDirt.setColor(Color(96, 96, 96));
  // TODO: get color here, now hardcoded. mBackgroundDirt.setColor(mColorScheme.dirt());
}

void FlappyCatFloor::reset() {

  mFloorSpikes.reset();
}

const Shape& FlappyCatFloor::boundingBox() const {

  return mFloor;
}



















