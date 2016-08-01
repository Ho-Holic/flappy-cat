// self
#include "AndroidApplication.h"

// stl
#include <functional>

AndroidApplication::AndroidApplication(ANativeActivity* activity,
                                       void* savedState,
                                       size_t savedStateSize)
: mActivity(activity)
, mMutex()
, mConditionVariable()
, mIsRunning(false)
, mConfiguration(nullptr, &AConfiguration_delete) {
  UNUSED(savedState);     // we don't save and load state for now
  UNUSED(savedStateSize); // --/--
}

void AndroidApplication::waitForStarted() {

  std::unique_lock<std::mutex> lock(mMutex);
  mConditionVariable.wait(lock, std::bind(&AndroidApplication::isRunning, std::ref(*this)));
  mMutex.unlock();
}

bool AndroidApplication::isRunning() const {

  return mIsRunning;
}

void AndroidApplication::exec() {

  initialize();

  SCOPE("application is initialized now") {
    std::lock_guard<std::mutex> lock(mMutex);
    UNUSED(lock);
    mIsRunning = true;
    mConditionVariable.notify_all();
  }

#warning start event loop here

#warning free some application resources on exit
}

void AndroidApplication::initialize() {

  // load configuration
  mConfiguration.reset(AConfiguration_new());
  AConfiguration_fromAssetManager(mConfiguration.get(), mActivity->assetManager);
  
#warning print configuration

}
