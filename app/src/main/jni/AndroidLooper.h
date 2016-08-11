#ifndef FLAPPY_CAT_ANDROIDLOOPER_H
#define FLAPPY_CAT_ANDROIDLOOPER_H

// ndk
#include <android/looper.h>

// self
#include "Guidelines.h"
#include "AndroidPipe.h"


class AndroidLooper {
  DISABLE_COPY(AndroidLooper)

public:
  // TODO: forward declare this class later
  struct PollSource {
    // meh, nothing here for now
  };

public:
  enum Id : int {
    ReservedId,
    MainId,
    InputQueueId,
  };

public:
  AndroidLooper();

public:
  void prepare();

private:
  ALooper* mLooper;
  AndroidPipe mPipe;
  PollSource mMainPollSource;
  PollSource mInputQueuePollSource;
};


#endif //FLAPPY_CAT_ANDROIDLOOPER_H
