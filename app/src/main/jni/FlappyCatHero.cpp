// self
#include <prototype/RectangleShape.h>
#include "FlappyCatHero.h"

FlappyCatHero::FlappyCatHero(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mBall()
, mResetModifier([](entity_type&){})
, mUpdateModifier([](entity_type&, const FrameDuration&){}) {
  //
}

float FlappyCatHero::radius() const {

  return mBall.geometry().radius();
}

void FlappyCatHero::setRadius(float radius) {

  mBall.geometry().setRadius(radius);
}

void FlappyCatHero::moveTo(const Position& position) {

  mBall.transformation().setPosition(position);
}

void FlappyCatHero::update(const FrameDuration& time) {

  FlappyCatEntity::update(time);
  mUpdateModifier(*this, time);
}

void FlappyCatHero::drawOn(const Window& window) const {

  // coordinates
  Position::value_type diameter = mBall.geometry().radius() * 2.f;
  Position bodyPos = mBall.transformation().position()
                     + Position(diameter * 0.3f, diameter * 0.3f);

  Position bodySize(diameter * 0.5f, diameter * 0.25f);

  Position headPos(bodySize.x() * 0.6f, bodySize.y() * 0.75f);
  Position headSize(diameter * 0.28f, diameter * 0.22f);

  Position backLegPos(0.f, -bodySize.y() * 0.75f);
  Position frontLegPos(bodySize.x() * 0.625f, 0.f);
  Position legAndTailSize(bodySize.x() * 0.15f, bodySize.y() * 1.f);
  Position tailPos(0.f, bodySize.y() * 0.35f);

  Position earSize(bodySize.x() * 0.2f, bodySize.y() * 0.75f);
  Position leftEarPos(0.f, headSize.y());
  Position rightEarPos(headSize.x() - earSize.x(), 0.f);

  Position eyeSize(headSize.x() * 0.25f, headSize.x() * 0.25f);
  Position leftEyePos(headSize.x() * 0.14f, headSize.y() * 0.5f);
  Position rightEyePos(bodySize.x() * 0.3f, 0.f);

  Position scarfSize(bodySize.x() * 0.75f, bodySize.y() * 0.42f);
  Position scarfPos(bodySize.x() * 0.34f, bodySize.y() * 0.42f);

  Position scarfTailSize(scarfSize.x() * 0.2f, scarfSize.y() * 1.5f);
  Position scarfTailPos(scarfSize.x() * 0.1f,  -scarfSize.y() * 0.7f);

  Position mouthSize(headSize.x() * 0.1f, headSize.y() * 0.08f);
  Position mouthPos(headSize.x() * 0.5f, headSize.y() * 0.22f);

  // objects
  RectangleShape body(bodyPos, bodySize);
  RectangleShape head(bodyPos + headPos, headSize);
  head.render().setBrushColor(Color(255, 0, 0));
  head.render().update(head);
  RectangleShape backLeg(bodyPos + backLegPos, legAndTailSize);
  RectangleShape frontLeg(bodyPos + backLegPos + frontLegPos, legAndTailSize);
  RectangleShape tail(bodyPos + tailPos, legAndTailSize);
  tail.render().setBrushColor(Color(255, 0, 0));
  tail.render().update(tail);

  // objects for ears (triangles)
  Position earPos = bodyPos + headPos;
  Vertices leftEar;
  leftEar << Vertex(earPos + leftEarPos + Position(0.f, earSize.y()),  Color(0,0,0))
          << Vertex(earPos + leftEarPos + Position(0.f, 0.f), Color(0,0,0))
          << Vertex(earPos + leftEarPos + Position(earSize.x(), 0.f),  Color(0,0,0));

  Vertices rightEar;
  rightEar << Vertex(earPos + leftEarPos + rightEarPos + Position(0.f, earSize.y()),  Color(0,0,0))
           << Vertex(earPos + leftEarPos + rightEarPos + Position(0.f, 0.f), Color(0,0,0))
           << Vertex(earPos + leftEarPos + rightEarPos + Position(earSize.x(), 0.f),
                     Color(0,0,0));

  RectangleShape leftEye(bodyPos + headPos + leftEyePos, eyeSize);
  RectangleShape rightEye(bodyPos + headPos + leftEyePos + rightEyePos, eyeSize);

  RectangleShape scarf(bodyPos + scarfPos, scarfSize);
  scarf.render().setBrushColor(Color(0, 0, 255));
  scarf.render().update(scarf);

  RectangleShape scarfTail(bodyPos + scarfPos + scarfTailPos, scarfTailSize);
  scarfTail.render().setBrushColor(Color(0, 255, 255));
  scarfTail.render().update(scarfTail);

  RectangleShape mouth(bodyPos + headPos + mouthPos, mouthSize);


  // draw
  window.draw(mBall);
  window.draw(body);
  window.draw(backLeg);
  window.draw(frontLeg);
  window.draw(tail);
  window.draw(scarf);
  window.draw(scarfTail);
  window.draw(head);
  window.drawVertices(leftEar, window.view());
  window.drawVertices(rightEar, window.view());
  window.draw(leftEye);
  window.draw(rightEye);
  window.draw(mouth);
}

const Position& FlappyCatHero::position() const {

  return mBall.transformation().position();
}

void FlappyCatHero::reset() {

  FlappyCatEntity::reset();
  mResetModifier(*this);
}

void FlappyCatHero::setResetModifier(const modifier_type& modifier) {

  mResetModifier = modifier;
}

void FlappyCatHero::setColor(const Color& color) {

  mBall.setColor(color);
}

void FlappyCatHero::setUpdateModifier(const update_modifier_type& modifier) {

  mUpdateModifier = modifier;
}
