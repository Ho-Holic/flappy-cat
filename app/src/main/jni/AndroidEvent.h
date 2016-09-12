#ifndef FLAPPY_CAT_ANDROIDEVENT_H
#define FLAPPY_CAT_ANDROIDEVENT_H

// stl
#include <cstdint>

// self
#include "Guidelines.h"

class AndroidEvent {
public:
  enum EventType : int8_t;

public:
  struct MoveEvent {

  };

public:
  union {
    MoveEvent moveEvent;
  };

public:
  AndroidEvent();
  AndroidEvent(EventType eventType);

public:
  EventType type() const;
  void setEventType(EventType eventType);

private:
  EventType mEventType;
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
};

#endif //FLAPPY_CAT_ANDROIDEVENT_H
