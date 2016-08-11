// self
#include "AndroidApplication.h"
#include "Log.h"

// stl
#include <functional>

AndroidApplication::AndroidApplication(ANativeActivity* activity,
                                       void* savedState,
                                       size_t savedStateSize)
: mActivity(activity)
, mMutex()
, mConditionVariable()
, mIsRunning(false)
, mIsDestroyed(false)
, mConfiguration()
, mLooper() {
  UNUSED(savedState);     // we don't save and load state for now
  UNUSED(savedStateSize); // --/--
}

void AndroidApplication::waitForStarted() {

  std::unique_lock<std::mutex> lock(mMutex);
  mConditionVariable.wait(lock, std::bind(&AndroidApplication::isRunning, std::ref(*this)));
  mMutex.unlock();
}

void AndroidApplication::requestDestruction() {

  std::unique_lock<std::mutex> lock(mMutex);

#warning write command to break an event loop

  mConditionVariable.wait(lock, std::bind(&AndroidApplication::isDestroyed, std::ref(*this)));
  mMutex.unlock();
}

bool AndroidApplication::isRunning() const {

  return mIsRunning;
}

bool AndroidApplication::isDestroyed() const {

  return mIsDestroyed;
}

void AndroidApplication::exec() {

  initialize();

  SCOPE("application is initialized now") {
    std::lock_guard<std::mutex> lock(mMutex);
    UNUSED(lock); // unlocks when goes out of a scope
    mIsRunning = true;
    mConditionVariable.notify_all();
  }

  forever() {
#warning main loop here
    break;
  }

  deinitialize();
}

void AndroidApplication::initialize() {

  // load configuration
  mConfiguration.reloadFrom(mActivity->assetManager);
  Log::i(TAG, mConfiguration.toString());

  // prepare looper for this thread to read events
  mLooper.prepare();

}

void AndroidApplication::deinitialize() {

  Log::i(TAG, "android_app_destroy!");

#warning free saved state

  std::lock_guard<std::mutex> lock(mMutex);
  UNUSED(lock); // unlocks when goes out of a scope

#warning detach looper from event queue

  mConfiguration.reset();

  mIsDestroyed = true;

  mConditionVariable.notify_all();

  CAUTION("If you `unlock` mutex, you can't touch `this` object");
}
