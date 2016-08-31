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
  NoDataAvailableEventType = -1,
  EmptyEventType           = 0,

  ActivityStartEventType,
  ActivityResumeEventType,
  ActivityPauseEventType,
  ActivityStopEventType,

  GainFocusEventType,
  LostFocusEventType,
};

#endif //FLAPPY_CAT_ANDROIDEVENT_H
