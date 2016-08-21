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


