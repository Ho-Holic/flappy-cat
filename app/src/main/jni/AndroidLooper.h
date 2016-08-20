#ifndef FLAPPY_CAT_ANDROIDLOOPER_H
#define FLAPPY_CAT_ANDROIDLOOPER_H

// ndk
#include <android/looper.h>

// self
#include "Guidelines.h"
#include "AndroidPipe.h"
#include "AndroidEvent.h"

// stl
#include <cstdint>


class AndroidLooper {
  DISABLE_COPY(AndroidLooper)

public:
  enum Id        : int;
  enum Timeout   : int;
  enum EventType : int8_t;

public:
  AndroidLooper();

public:
  void prepare();
  bool pollEvent(AndroidEvent& event);
  void postEvent(EventType eventType);

private:
  void pollFromAndroidCallbacks(AndroidEvent& event);
  void pollFromInputQueue(AndroidEvent& event);
  void unexpectedIdentifier(int id);

private:
  ALooper* mLooper;
  AndroidPipe mPipe;
};

// enums

enum AndroidLooper::Id : int {
  ReservedId,
  AndroidCallbackId,
  InputQueueId,
};

enum AndroidLooper::Timeout : int {
  IndefinitelyUntilEventAppearsTimeout = -1,
  ImmediatelyWithoutBlockingTimeout    = 0,
};

enum AndroidLooper::EventType : int8_t {
  NoDataAvailableEvent = -1,
  ActivityStartEvent   = 0,
  ActivityResumeEvent,
  ActivityPauseEvent,
  ActivityStopEvent,
};


#endif //FLAPPY_CAT_ANDROIDLOOPER_H
