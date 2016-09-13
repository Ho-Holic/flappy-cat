#ifndef FLAPPY_CAT_ANDROIDEVENT_H
#define FLAPPY_CAT_ANDROIDEVENT_H

// stl
#include <cstdint>

// self
#include "AndroidEventData.h"
#include "Guidelines.h"

class AndroidEvent {
public:
  enum EventType : int8_t;

public:
  AndroidEvent();
  AndroidEvent(EventType eventType);

public:
  EventType type() const;
  void setEventType(EventType eventType);

public:
  void setMotionEventData(float x, float y);

public:
  const AndroidMotionEvent& motionEvent() const;

private:
  EventType mEventType;
  AndroidEventData mEventData;
};

// enums

enum AndroidEvent::EventType : int8_t {
  EmptyEventType,

  ActivityStartEventType,
  ActivityResumeEventType,
  ActivityPauseEventType,
  ActivityStopEventType,

  GainFocusEventType,
  LostFocusEventType,

  NativeWindowCreatedEventType,
  NativeWindowDestroyedEventType,

  MotionEventType,
};


#endif //FLAPPY_CAT_ANDROIDEVENT_H
