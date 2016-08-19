#ifndef FLAPPY_CAT_ANDROIDLOOPER_H
#define FLAPPY_CAT_ANDROIDLOOPER_H

// ndk
#include <android/looper.h>

// self
#include "Guidelines.h"
#include "AndroidPipe.h"
#include "AndroidEvent.h"


class AndroidLooper {
  DISABLE_COPY(AndroidLooper)

public:

  enum Id : int {
    ReservedId,
    MainId,
    InputQueueId,
  };

  enum Timeout : int {
    IndefinitelyUntilEventAppearsTimeout = -1,
    ImmediatelyWithoutBlockingTimeout = 0,
  };

public:
  AndroidLooper();

public:
  void prepare();
  bool pollEvent(AndroidEvent& event);

private:
  void unexpectedIdentifier(int id);

private:
  ALooper* mLooper;
  AndroidPipe mPipe;
};


#endif //FLAPPY_CAT_ANDROIDLOOPER_H
