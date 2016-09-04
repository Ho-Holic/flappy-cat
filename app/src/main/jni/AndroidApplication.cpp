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
, mIsDestroyRequested(false)
, mConfiguration(activity->assetManager)
, mLooper()
, mWindow()
, mEvents() {
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
  activity->callbacks->onNativeWindowResized   = &AndroidApplication::onNativeWindowResized;
  activity->callbacks->onNativeWindowRedrawNeeded = &AndroidApplication::onNativeWindowRedrawNeeded;
  activity->callbacks->onNativeWindowDestroyed = &AndroidApplication::onNativeWindowDestroyed;
  activity->callbacks->onInputQueueCreated     = &AndroidApplication::onInputQueueCreated;
  activity->callbacks->onInputQueueDestroyed   = &AndroidApplication::onInputQueueDestroyed;
  activity->callbacks->onContentRectChanged    = &AndroidApplication::onContentRectChanged;

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
  UNUSED(application); // not needed

  *outLen = 0;
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
  application->reloadConfiguration();
}

void AndroidApplication::onLowMemory(ANativeActivity* activity) {

  Log::i(TAG, "LowMemory: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  UNUSED(application); // not needed
}

void AndroidApplication::onWindowFocusChanged(ANativeActivity* activity, int hasFocus) {

  Log::i(TAG, "WindowFocusChanged: %p -- %d\n", activity, hasFocus);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  application->changeFocus(hasFocus ? GainFocus : LostFocus);
}

void AndroidApplication::onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {

  Log::i(TAG, "NativeWindowCreated: %p -- %p\n", activity, window);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  application->setNativeWindow(window);
}

void AndroidApplication::onNativeWindowResized(ANativeActivity* activity, ANativeWindow* window) {
  Log::i(TAG, "NativeWindowResized: %p -- %p\n", activity, window);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void AndroidApplication::onNativeWindowRedrawNeeded(ANativeActivity* activity,
                                                    ANativeWindow* window) {

  Log::i(TAG, "NativeWindowRedrawNeeded: %p -- %p\n", activity, window);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);

}

void AndroidApplication::onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {

  Log::i(TAG, "NativeWindowDestroyed: %p -- %p\n", activity, window);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  application->setNativeWindow(nullptr);
}

void AndroidApplication::onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {

  Log::i(TAG, "InputQueueCreated: %p -- %p\n", activity, queue);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  application->setInputQueue(queue);
}

void AndroidApplication::onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {

  Log::i(TAG, "InputQueueDestroyed: %p -- %p\n", activity, queue);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  application->setInputQueue(nullptr);
}

void AndroidApplication::onContentRectChanged(ANativeActivity* activity, const ARect* rect) {

  Log::i(TAG, "ContentRectChanged: %p -- %d %d %d %d\n", activity,
         rect->left, rect->top, rect->right, rect->bottom);

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

  mIsDestroyRequested = true;

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

  return mIsDestroyRequested;
}

AndroidApplication::ActivityState AndroidApplication::activityState() const {

  return mActivityState;
}

void AndroidApplication::exec() {

  initialize();

  SCOPE("application is initialized now") {

    std::lock_guard<std::mutex> lock(mMutex);
    mIsRunning = true;
    mConditionVariable.notify_all();

    UNUSED(lock); // unlocks when goes out of a scope
  }

  // start `system event loop`

  // if native window is not ready wait for appropriate event
  // then enter user `main`, if window is not ready again fall back to
  // system event loop and wait for appropriate event again

  while ( ! isDestroyRequested()) {

    AndroidEvent event;
    while (pollEvent(event)) {
      processEvent(event);
    }

    if (mWindow.isReady()) {

      // start `user event loop`
      main();
    }
  }

  // clean up after event loop
  terminate();
}

void AndroidApplication::initialize() {

  // load configuration
  mConfiguration.reload();
  Log::i(TAG, mConfiguration.toString());

  // prepare looper for this thread to read events
  mLooper.prepare();

}

bool AndroidApplication::pollEvent(AndroidEvent& event) {

  bool hasEventsInLooper = mLooper.pollEvent(event);

  if (hasEventsInLooper) {
    postEvent(event);
  }

  if ( ! mEvents.empty()) {

    event = mEvents.front();
    mEvents.pop();

    processEvent(event);

    return true;
  }

  return false;
}

void AndroidApplication::postEvent(const AndroidEvent& event) {

  mEvents.push(event);
}

void AndroidApplication::processEvent(AndroidEvent& event) {

  CAUTION("Don't forget to lock mutex when you add new processing parts here"
          "If you touch class members of course");

  switch (event.type()) {

    case ActivityStartEventType:  setActivityState(StartActivityState);  break;
    case ActivityResumeEventType: setActivityState(ResumeActivityState); break;
    case ActivityPauseEventType:  setActivityState(PauseActivityState);  break;
    case ActivityStopEventType:   setActivityState(StopActivityState);   break;

    case NativeWindowCreatedEventType:   mWindow.initialize(); break;
    case NativeWindowDestroyedEventType: mWindow.terminate();  break;

    case EmptyEventType: break;
  }

}

void AndroidApplication::changeActivityStateTo(AndroidApplication::ActivityState activityState) {

  AndroidEvent event;
  switch (activityState) {
    case StartActivityState:  event.setEventType(ActivityStartEventType);  break;
    case ResumeActivityState: event.setEventType(ActivityResumeEventType); break;
    case PauseActivityState:  event.setEventType(ActivityPauseEventType);  break;
    case StopActivityState:   event.setEventType(ActivityStopEventType);   break;
    default: break;
  }

  auto isInState = [&activityState, this]() -> bool {

    return this->activityState() == activityState;
  };

  // wait for state to change
  std::unique_lock<std::mutex> lock(mMutex);

  this->postEvent(event);

  mConditionVariable.wait(lock, isInState);
  mMutex.unlock();
}


void AndroidApplication::setActivityState(AndroidApplication::ActivityState activityState) {

  Log::i(TAG, "activityState = %d\n", activityState);

  std::lock_guard<std::mutex> lock(mMutex);

  mActivityState = activityState;

  mConditionVariable.notify_all();

  UNUSED(lock); // unlocks when goes out of a scope
}

void AndroidApplication::setInputQueue(AInputQueue* queue) {

  std::lock_guard<std::mutex> lock(mMutex);

  mLooper.setInputQueue(queue);

  mConditionVariable.notify_all();

  UNUSED(lock); // unlocks when goes out of a scope
}

void AndroidApplication::setNativeWindow(ANativeWindow* window) {

  std::lock_guard<std::mutex> lock(mMutex);

  mWindow.setNativeWindow(window);

  AndroidEvent event(window ? NativeWindowCreatedEventType
                            : NativeWindowDestroyedEventType);
  this->postEvent(event);

  mConditionVariable.notify_all();

  UNUSED(lock); // unlocks when goes out of a scope

}

void AndroidApplication::reloadConfiguration() {

  std::lock_guard<std::mutex> lock(mMutex);

  mConfiguration.reload();
  Log::i(TAG, mConfiguration.toString());

  mConditionVariable.notify_all();

  UNUSED(lock); // unlocks when goes out of a scope
}

void AndroidApplication::changeFocus(AndroidApplication::Focus focus) {

  AndroidEvent event;
  switch (focus) {
    case GainFocus: event.setEventType(GainFocusEventType);  break;
    case LostFocus: event.setEventType(LostFocusEventType);  break;
    default: break;
  }

  std::lock_guard<std::mutex> lock(mMutex);

  this->postEvent(event);

  mConditionVariable.notify_all();

  UNUSED(lock); // unlocks when goes out of a scope
}

void AndroidApplication::terminate() {

  Log::i(TAG, "android_app_destroy!");

  std::lock_guard<std::mutex> lock(mMutex);

  mConfiguration.reset();

  mIsDestroyed = true;

  mConditionVariable.notify_all();

  UNUSED(lock); // unlocks when goes out of a scope

  CAUTION("If you `unlock` mutex, you can't touch `this` object");
}


