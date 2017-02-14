// self
#include "AndroidEvent.h"

// engine
#include <core/Log.h>

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


void AndroidEvent::setTouchEventData(float x, float y) {

  REQUIRE(TAG, mEventType == TouchEventType, "Must be 'MotionEventType'");

  mEventData.touchEvent.x = x;
  mEventData.touchEvent.y = y;
}

const AndroidTouchEvent& AndroidEvent::touchEvent() const {

  REQUIRE(TAG, mEventType == TouchEventType, "Must be 'MotionEventType'");

  return mEventData.touchEvent;
}

void AndroidEvent::setResizeEventData(int32_t width, int32_t height) {

  REQUIRE(TAG, mEventType == ResizedEventType, "Must be 'ResizedEventType'");

  mEventData.resizeEvent.width  = width;
  mEventData.resizeEvent.height = height;

}

const AndroidResizeEvent& AndroidEvent::resizeEvent() const {

  REQUIRE(TAG, mEventType == ResizedEventType, "Must be 'ResizedEventType'");

  return mEventData.resizeEvent;
}




