// self
#include "AndroidEvent.h"

AndroidEvent::AndroidEvent()
: AndroidEvent(EmptyEventType) {
  //
}

AndroidEvent::AndroidEvent(EventType eventType)
: mEventType(eventType) {
  //
}

AndroidEvent::EventType AndroidEvent::type() const {

  return mEventType;
}

void AndroidEvent::setEventType(EventType eventType) {

  mEventType = eventType;
}


void AndroidEvent::setMotionEventData(float x, float y) {

  REQUIRE(TAG, mEventType == MotionEventType, "Must be `MotionEventType`");

  mEventData.motionEvent.x = x;
  mEventData.motionEvent.y = y;
}

const AndroidMotionEvent& AndroidEvent::motionEvent() const {

  REQUIRE(TAG, mEventType == MotionEventType, "Must be `MotionEventType`");

  return mEventData.motionEvent;
}
