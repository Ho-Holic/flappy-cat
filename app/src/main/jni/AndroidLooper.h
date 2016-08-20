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
  enum Id      : int;
  enum Timeout : int;
  enum Command : int8_t;

public:
  AndroidLooper();

public:
  void prepare();
  bool pollEvent(AndroidEvent& event);

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

enum AndroidLooper::Command : int8_t {
  NoDataAvailableCommand = -1,
  FirstCommand = 0,
};


#endif //FLAPPY_CAT_ANDROIDLOOPER_H
