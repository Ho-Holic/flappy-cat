#ifndef FLAPPY_CAT_ANDROIDEVENT_H
#define FLAPPY_CAT_ANDROIDEVENT_H

// stl
#include <cstdint>

// engine
#include "AndroidEventData.h"

// style
#include "style/Guidelines.h"

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
  void setTouchEventData(float x, float y);
  void setResizeEventData(int32_t width, int32_t height);

public:
  const AndroidTouchEvent& touchEvent() const;
  const AndroidResizeEvent& resizeEvent() const;

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

  ResizedEventType,
  TouchEventType
};


#endif //FLAPPY_CAT_ANDROIDEVENT_H
