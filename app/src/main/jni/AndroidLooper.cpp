// self
#include "AndroidLooper.h"
#include "Log.h"

AndroidLooper::AndroidLooper()
: mLooper(nullptr)
, mInputQueue(nullptr, &AInputQueue_detachLooper) {
  //
}

void AndroidLooper::prepare() {

  REQUIRE(TAG, mLooper == nullptr, "must prepare looper once");

  // don't move it to constructor
  mLooper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);

}

void AndroidLooper::setInputQueue(AInputQueue* inputQueue) {

  mInputQueue.reset(inputQueue);

  if (mInputQueue) {
    AInputQueue_attachLooper(mInputQueue.get(),
                             mLooper, InputQueueId,
                             nullptr, nullptr);
  }
}

bool AndroidLooper::pollEvent(AndroidEvent& event) {

  int id = ALooper_pollAll(ImmediatelyWithoutBlockingTimeout,
                           nullptr, nullptr, nullptr);
  switch (id) {
    case InputQueueId: pollFromInputQueue(event); break;
    case ALOOPER_POLL_TIMEOUT: break;
    default: unexpectedIdentifier(id); break;
  }

  bool hasAnyEvents = (id >= 0);
  return hasAnyEvents;
}

void AndroidLooper::pollFromInputQueue(AndroidEvent& event) {

  AInputQueue* queue = mInputQueue.get();

  AInputEvent* inputEvent = nullptr;

  int32_t nextEvent = AInputQueue_getEvent(queue, &inputEvent);

  if (nextEvent >= 0) {

    if (AInputQueue_preDispatchEvent(queue, inputEvent)) {
      return;
    }

    int32_t handled = 0;

    int32_t type = AInputEvent_getType(inputEvent);

    if (type == AINPUT_EVENT_TYPE_MOTION) {

      int32_t action = AMotionEvent_getAction(inputEvent);

      switch (action & AMOTION_EVENT_ACTION_MASK) {
      case AMOTION_EVENT_ACTION_MOVE: handled = pollMotionMove(inputEvent, event); break;


      }

    }

    AInputQueue_finishEvent(queue, inputEvent, handled);

  }

}

void AndroidLooper::unexpectedIdentifier(int id) {

  Log::i(TAG, "Unexpected identifier in pollEvent = %d", id);
}


int32_t AndroidLooper::pollMotionMove(AInputEvent* inputEvent, AndroidEvent& event) {
  
  return 0;
}
