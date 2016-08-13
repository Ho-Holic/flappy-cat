// ndk
#include <android/native_activity.h>

// self
#include "AndroidApplication.h"
#include "Log.h"

// std
#include <thread>

//  Hello! This is a list of some conventions and decisions made for this project:
//
//    1. Namespaces not used - project too small
//
//    2. Java   `Log::i(TAG, "Creating: %p\n", activity);` was prefered to
//       C++ish `log_i(TAG) << "Creating: " << activity << "\n";` because of confusion
//       with std::log() function and less error prone implementation
//
//    3. Macro `DISABLE_COPY` prefered to manual `= delete` because of easy search and maintenance
//
//    4. Initialize smart pointers  `shared_ptr(nullptr)` instead of `shared_ptr()`
//       for readability and back compatibility with raw pointers
//
//    5. Yse of UNUSED macro for every case, even if I can omit it in well
//       known places like `std::lock_guard`
//

//  Known errors, glitches and strange behaviour
//
//    1. Linker error `unused DT entry: type blahhh arg blabla`
//       http://stackoverflow.com/questions/33206409/unused-dt-entry-type-0x1d-arg
//
//    2. app/build.gradle link against `atomic`

static void* createAndroidApplication(ANativeActivity* activity,
                                      void* savedState,
                                      size_t savedStateSize);

static void onDestroy(ANativeActivity* activity);
static void onStart(ANativeActivity* activity);
static void onResume(ANativeActivity* activity);
static void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen);
static void onPause(ANativeActivity* activity);
static void onStop(ANativeActivity* activity);
static void onConfigurationChanged(ANativeActivity* activity);
static void onLowMemory(ANativeActivity* activity);
static void onWindowFocusChanged(ANativeActivity* activity, int focused);
static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window);
static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window);
static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue);
static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue);

extern "C" {
  void ANativeActivity_onCreate(ANativeActivity *activity,
                                void *savedState,
                                size_t savedStateSize) {

    Log::i(TAG, "Creating: %p\n", activity);
    activity->callbacks->onDestroy = onDestroy;
    activity->callbacks->onStart = onStart;
    activity->callbacks->onResume = onResume;
    activity->callbacks->onSaveInstanceState = onSaveInstanceState;
    activity->callbacks->onPause = onPause;
    activity->callbacks->onStop = onStop;
    activity->callbacks->onConfigurationChanged = onConfigurationChanged;
    activity->callbacks->onLowMemory = onLowMemory;
    activity->callbacks->onWindowFocusChanged = onWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated = onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;
    activity->instance = createAndroidApplication(activity, savedState, savedStateSize);
  }
}

void* createAndroidApplication(ANativeActivity* activity,
                               void* savedState,
                               size_t savedStateSize) {

  AndroidApplication* application = new AndroidApplication(activity, savedState, savedStateSize);

  // Create `event handler` thread
  //   - don't capture `application` pointer, this would produce less readable code
  auto eventHandlerTask = [](AndroidApplication* application)->void {
    application->exec();
  };

  std::thread eventHandlerThread(std::ref(eventHandlerTask), std::ref(application));
  eventHandlerThread.detach();

  // Wait until `eventHandlerTask` properly lunch the event loop
  application->waitForStarted();

  return application;
}

void onDestroy(ANativeActivity* activity) {

  Log::i(TAG, "Destroy: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  application->requestDestruction();

  delete application;
}

void onStart(ANativeActivity* activity) {

  Log::i(TAG, "Start: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void onResume(ANativeActivity* activity) {

  Log::i(TAG, "Resume: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen) {

  Log::i(TAG, "SaveInstanceState: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
  return nullptr;
}

void onPause(ANativeActivity* activity) {

  Log::i(TAG, "Pause: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void onStop(ANativeActivity* activity) {

  Log::i(TAG, "Stop: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void onConfigurationChanged(ANativeActivity* activity) {

  Log::i(TAG, "ConfigurationChanged: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void onLowMemory(ANativeActivity* activity) {

  Log::i(TAG, "LowMemory: %p\n", activity);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void onWindowFocusChanged(ANativeActivity* activity, int focused) {

  Log::i(TAG, "WindowFocusChanged: %p -- %d\n", activity, focused);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {

  Log::i(TAG, "NativeWindowCreated: %p -- %p\n", activity, window);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {

  Log::i(TAG, "NativeWindowDestroyed: %p -- %p\n", activity, window);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {

  Log::i(TAG, "InputQueueCreated: %p -- %p\n", activity, queue);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}

void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {

  Log::i(TAG, "InputQueueDestroyed: %p -- %p\n", activity, queue);

  AndroidApplication* application = static_cast<AndroidApplication*>(activity->instance);
}