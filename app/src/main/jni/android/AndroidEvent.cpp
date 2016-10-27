// self
#include "AndroidEvent.h"
#include "Log.h"

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

void AndroidEvent::setResizeEventData(int32_t width, int32_t height) {

  REQUIRE(TAG, mEventType == ResizedEventType, "Must be `ResizedEventType`");

  mEventData.resizeEvent.width  = width;
  mEventData.resizeEvent.height = height;

}

const AndroidResizeEvent& AndroidEvent::resizeEvent() const {

  REQUIRE(TAG, mEventType == ResizedEventType, "Must be `ResizedEventType`");

  return mEventData.resizeEvent;
}




