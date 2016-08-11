// self
#include "AndroidLooper.h"
#include "Log.h"

AndroidLooper::AndroidLooper()
: mLooper(nullptr)
, mPipe()
, mMainPollSource()
, mInputQueuePollSource() {
  //
}


void AndroidLooper::prepare() {

  REQUIRE(TAG, mLooper == nullptr, "must prepare looper once");

#warning initialize mMainPollSource
#warning initialize mInputQueuePollSource

  mLooper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);

  ALooper_addFd(mLooper, mPipe.readEnd(),
                AndroidLooper::MainId, ALOOPER_EVENT_INPUT,
                nullptr, &mMainPollSource);
}
