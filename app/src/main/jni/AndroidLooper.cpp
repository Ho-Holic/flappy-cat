// self
#include "AndroidLooper.h"
#include "Log.h"

AndroidLooper::AndroidLooper()
: mLooper(nullptr)
, mPipe() {
  //
}


void AndroidLooper::prepare() {

  REQUIRE(TAG, mLooper == nullptr, "must prepare looper once");

  mLooper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);

  ALooper_addFd(mLooper, mPipe.readEnd(),
                AndroidLooper::MainId, ALOOPER_EVENT_INPUT,
                nullptr, nullptr);
}


bool AndroidLooper::pollEvent(AndroidEvent& event) {

  int id = ALooper_pollAll(ImmediatelyWithoutBlockingTimeout,
                           nullptr, nullptr, nullptr);

  switch (id) {
    case MainId:       break;
    case InputQueueId: break;
    default: unexpectedIdentifier(id); break;
  }


  bool hasAnyEvents = (id >= 0);
  return hasAnyEvents;
}

void AndroidLooper::unexpectedIdentifier(int id) {

  Log::i(TAG, "Unexpected identifier in pollEvent = %d", id);
}
