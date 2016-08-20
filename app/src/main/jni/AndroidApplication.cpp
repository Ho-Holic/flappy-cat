// self
#include "AndroidApplication.h"
#include "Log.h"

// stl
#include <functional>

AndroidApplication::AndroidApplication(ANativeActivity* activity,
                                       void* savedState,
                                       size_t savedStateSize)
: mActivity(activity)
, mActivityState(InitializationActivityState)
, mMutex()
, mConditionVariable()
, mIsRunning(false)
, mIsDestroyed(false)
, mConfiguration()
, mLooper() {
  UNUSED(savedState);     // we don't save and load state for now
  UNUSED(savedStateSize); // --/--

  activity->callbacks->onDestroy               = &AndroidApplication::onDestroy;
  activity->callbacks->onStart                 = &AndroidApplication::onStart;
  activity->callbacks->onResume                = &AndroidApplication::onResume;
  activity->callbacks->onSaveInstanceState     = &AndroidApplication::onSaveInstanceState;
  activity->callbacks->onPause                 = &AndroidApplication::onPause;
  activity->callbacks->onStop                  = &AndroidApplication::onStop;
  activity->callbacks->onConfigurationChanged  = &AndroidApplication::onConfigurationChanged;
  activity->callbacks->onLowMemory             = &AndroidApplication::onLowMemory;
  activity->callbacks->onWindowFocusChanged    = &AndroidApplication::onWindowFocusChanged;
  activity->callbacks->onNativeWindowCreated   = &AndroidApplication::onNativeWindowCreated;
  activity->callbacks->onNativeWindowDestroyed = &AndroidApplication::onNativeWindowDestroyed;
  activity->callbacks->onInputQueueCreated     = &AndroidApplication::onInputQueueCreated;
  activity->callbacks->onInputQueueDestroyed   = &AndroidApplication::onInputQueueDestroyed;

  CAUTION("Memory allocated before constructor so we can assign `this` here, but if you"
          "want to move this code from constructor and assign to pointer of class that extends"
          "AndroidApplication, you must cast to AndroidApplication, because callbacks would"
          "downcast from `void*` and you would get problems under virtual inheritance."
          "You would get wrong address, so do this please:"
          "`activity->instance = static_cast<AndroidApplication*>(derivedPointer)`");
  activity->instance = this;
}

AndroidApplication::~AndroidApplication() {
  // this destructor intentionally left blank and moved to `.cpp` file
  Log::i(TAG, "Deleted! \n"); // delete this line when app is done
}

void AndroidApplication::onDestroy(ANativeActivity* activity) {

  Log::i(TAG, "Destroy: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  application->requestDestruction();

  delete application;
}

// callbacks

void AndroidApplication::onStart(ANativeActivity* activity) {

  Log::i(TAG, "Start: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  application->changeActivityStateTo(StartActivityState);
}

void AndroidApplication::onResume(ANativeActivity* activity) {

  Log::i(TAG, "Resume: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  application->changeActivityStateTo(ResumeActivityState);
}

void* AndroidApplication::onSaveInstanceState(ANativeActivity* activity, size_t* outLen) {

  Log::i(TAG, "SaveInstanceState: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  return nullptr;
}

void AndroidApplication::onPause(ANativeActivity* activity) {

  Log::i(TAG, "Pause: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  application->changeActivityStateTo(PauseActivityState);
}

void AndroidApplication::onStop(ANativeActivity* activity) {

  Log::i(TAG, "Stop: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  application->changeActivityStateTo(StopActivityState);
}

void AndroidApplication::onConfigurationChanged(ANativeActivity* activity) {

  Log::i(TAG, "ConfigurationChanged: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void AndroidApplication::onLowMemory(ANativeActivity* activity) {

  Log::i(TAG, "LowMemory: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void AndroidApplication::onWindowFocusChanged(ANativeActivity* activity, int focused) {

  Log::i(TAG, "WindowFocusChanged: %p -- %d\n", activity, focused);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void AndroidApplication::onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {

  Log::i(TAG, "NativeWindowCreated: %p -- %p\n", activity, window);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void AndroidApplication::onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {

  Log::i(TAG, "NativeWindowDestroyed: %p -- %p\n", activity, window);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void AndroidApplication::onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {

  Log::i(TAG, "InputQueueCreated: %p -- %p\n", activity, queue);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void AndroidApplication::onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {

  Log::i(TAG, "InputQueueDestroyed: %p -- %p\n", activity, queue);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

// main code

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

bool AndroidApplication::isDestroyRequested() const {
#warning write code here
  return false;
}

AndroidApplication::ActivityState AndroidApplication::activityState() const {
  return mActivityState;
}

void AndroidApplication::exec() {

  initialize();

  SCOPE("application is initialized now") {
    std::lock_guard<std::mutex> lock(mMutex);
    UNUSED(lock); // unlocks when goes out of a scope
    mIsRunning = true;
    mConditionVariable.notify_all();
  }

  main();

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



bool AndroidApplication::pollEvent(AndroidEvent& event) {

  //if (event.eventType() == EmptyEvent) {
  //  postProcessOfPreviousEvent(event);
  //}

  bool hasAnyEvents = mLooper.pollEvent(event);
  //preProcessEvent(event);
  return hasAnyEvents;
}

void AndroidApplication::changeActivityStateTo(AndroidApplication::ActivityState activityState) {

  // function for checking when state of activity changed
  auto isInState = [&activityState, this]() -> bool {

    return this->activityState() == activityState;
  };


  std::unique_lock<std::mutex> lock(mMutex);

  // One can try to remove `mLooper.postEvent` duplicated code but would
  // produce less readable code
  switch (activityState) {
    case StartActivityState:  mLooper.postEvent(ActivityStartEvent);  break;
    case ResumeActivityState: mLooper.postEvent(ActivityResumeEvent); break;
    case PauseActivityState:  mLooper.postEvent(ActivityPauseEvent);  break;
    case StopActivityState:   mLooper.postEvent(ActivityStopEvent);   break;
    default: break;
  }

  mConditionVariable.wait(lock, isInState);
  mMutex.unlock();
}


