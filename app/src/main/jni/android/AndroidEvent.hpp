#ifndef FLAPPY_CAT_ANDROIDEVENT_H
#define FLAPPY_CAT_ANDROIDEVENT_H

// stl
#include <cstdint>

// engine
#include "AndroidEventData.hpp"

// style
#include "style/Guidelines.hpp"

// ndk
#include <android/native_activity.h>

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
  void setNativeWindowEventData(ANativeWindow* pendingWindow);
  void setInputQueueEventData(AInputQueue* pendingQueue);
  void setEventLoopEventData(bool windowReady);

public:
  const AndroidTouchEvent& touchEvent() const;
  const AndroidResizeEvent& resizeEvent() const;
  const AndroidNativeWindowEvent& nativeWindowEvent() const;
  const AndroidInputQueueEvent& inputQueueEvent() const;
  const AndroidEventLoopEvent& eventLoopEvent() const;

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

  InputQueueCreatedEventType,
  InputQueueDestroyedEventType,

  ResizedEventType,
  TouchEventType,
  EventLoopEventType,
};


#endif //FLAPPY_CAT_ANDROIDEVENT_H
