// self
#include "AndroidLooper.h"

// engine
#include <core/Log.h>

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

    int32_t handled = dispatchEvent(inputEvent, event);

    AInputQueue_finishEvent(queue, inputEvent, handled);

  }

}

int32_t AndroidLooper::dispatchEvent(AInputEvent* inputEvent, AndroidEvent& event) {

  int32_t type = AInputEvent_getType(inputEvent);

  switch (type) {
    case AINPUT_EVENT_TYPE_MOTION: return dispatchMotionEvent(inputEvent, event); break;
    case AINPUT_EVENT_TYPE_KEY:    return dispatchKeyEvent(inputEvent, event);    break;
  }

  return 0;
}

int32_t AndroidLooper::dispatchMotionEvent(AInputEvent* inputEvent, AndroidEvent& event) {

  int32_t action = AMotionEvent_getAction(inputEvent);

  switch (action & AMOTION_EVENT_ACTION_MASK) {
    case AMOTION_EVENT_ACTION_UP: return dispatchTouchEvent(inputEvent, event); break;
  }

  return 0;
}

int32_t AndroidLooper::dispatchTouchEvent(AInputEvent* inputEvent, AndroidEvent& event) {

  float x = AMotionEvent_getX(inputEvent, 0);
  float y = AMotionEvent_getY(inputEvent, 0);

  event.setEventType(AndroidEvent::EventType::TouchEventType);
  event.setTouchEventData(x, y);

  return 1;
}

int32_t AndroidLooper::dispatchKeyEvent(AInputEvent* inputEvent, AndroidEvent& event) {

  UNUSED(inputEvent); // for later usage
  UNUSED(event);      // for later usage

  Log::i(TAG, "Key event");

  return 0;
}


void AndroidLooper::unexpectedIdentifier(int id) {

  Log::i(TAG, "Unexpected identifier in pollEvent = %d", id);
}


