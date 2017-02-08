// self
#include "FlappyCatCloud.h"

// engine
#include <core/Log.h>
#include <style/Guidelines.h>

FlappyCatCloud::FlappyCatCloud(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mCloudParts()
, mResetModifier([](entity_type&){}){
  //
}

void FlappyCatCloud::initialize() {

  // TODO: parametrize reserve function
  mCloudParts.reserve(120);

  size_t cloudCount = 100;

  for (size_t i = 0; i < cloudCount; ++i) {
    mCloudParts.emplace_back(Position(0.f, 0.f), 50.f, 32);
  }
}

void FlappyCatCloud::setResetModifier(const modifier_type& modifier) {
  mResetModifier = modifier;
}

void FlappyCatCloud::reset() {

  for (size_t i = 0; i < mCloudParts.size(); ++i) {

    REQUIRE(TAG, mResetModifier != nullptr, "Reset modifier must be not null");

    mResetModifier(mCloudParts[i]);

  }

}

void FlappyCatCloud::drawOn(const Window& window) const {

  for (const entity_type& part : mCloudParts)  {
    // TODO: make game circle abstraction from entity
    // part.drawOn(window);
    window.draw(part);
  }
}

const Position& FlappyCatCloud::position() const {
  return Position(0.f, 0.f);
}

void FlappyCatCloud::moveTo(const Position& position) {
  //
}

void FlappyCatCloud::setColor(const Color& color) {
  //
}















