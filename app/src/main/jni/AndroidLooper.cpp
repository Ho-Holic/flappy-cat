// self
#include "AndroidLooper.h"
#include "Log.h"

AndroidLooper::AndroidLooper()
: mLooper(nullptr)
, mInputQueue(nullptr, &AInputQueue_detachLooper)
, mPipe() {
  //
}

void AndroidLooper::prepare() {

  REQUIRE(TAG, mLooper == nullptr, "must prepare looper once");

  // don't move it to constructor
  mLooper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);

  ALooper_addFd(mLooper, mPipe.readEnd(),
                AndroidCallbackId, ALOOPER_EVENT_INPUT,
                nullptr, nullptr);
}

void AndroidLooper::setInputQueue(AInputQueue* inputQueue) {

  mInputQueue.reset(inputQueue);

  if (mInputQueue) {
    AInputQueue_attachLooper(mInputQueue.get(),
                             mLooper, InputQueueId,
                             nullptr, nullptr);
  }
}

void AndroidLooper::postEvent(const AndroidEvent& event) {

  mPipe.writeEnum<AndroidEvent::EventType>(event.type());
}

bool AndroidLooper::pollEvent(AndroidEvent& event) {

  int id = ALooper_pollAll(ImmediatelyWithoutBlockingTimeout,
                           nullptr, nullptr, nullptr);
  switch (id) {
    case AndroidCallbackId:  pollFromAndroidCallbacks(event); break;
    case InputQueueId:       pollFromInputQueue(event);       break;
    default:                 unexpectedIdentifier(id);        break;
  }

  bool hasAnyEvents = (id >= 0);
  return hasAnyEvents;
}

void AndroidLooper::pollFromAndroidCallbacks(AndroidEvent& event) {

  AndroidEvent::EventType eventType = mPipe.readEnum<AndroidEvent::EventType,
                                                     NoDataAvailableEventType>();
  switch (eventType) {
    //
  }
}

void AndroidLooper::pollFromInputQueue(AndroidEvent& event) {

  AInputQueue* queue = mInputQueue.get();

  AInputEvent* inputEvent = nullptr;

  int32_t nextEvent = AInputQueue_getEvent(queue, &inputEvent);

  if (nextEvent >= 0) {

    Log::i(TAG, "New input event: type = %d\n", AInputEvent_getType(inputEvent));

    if (AInputQueue_preDispatchEvent(queue, inputEvent)) {
      return;
    }

    int32_t handled = 0;

    // user code
    //if (app->onInputEvent != NULL) handled = app->onInputEvent(app, event);

    AInputQueue_finishEvent(queue, inputEvent, handled);

  }
  else {

    Log::i(TAG, "Failure reading next input event: %s\n", strerror(errno));
  }

}

void AndroidLooper::unexpectedIdentifier(int id) {

  Log::i(TAG, "Unexpected identifier in pollEvent = %d", id);
}



