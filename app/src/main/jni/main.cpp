// ndk
#include <android/native_activity.h>

// self
#include "AndroidApplication.h"
#include "Log.h"

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

static void* createAndroidApplication(ANativeActivity* activity,
                                      void* savedState,
                                      size_t savedStateSize);

//  Hello! This is a list of some conventions and decisions made for this project:
//    1. Namespaces not used - project too small
//    2. Java   `Log::i(TAG, "Creating: %p\n", activity);` was prefered to
//       C++ish `log_i(TAG) << "Creating: " << activity << "\n";` because of confusion
//       with std::log() function and ease of implementation

// entry point. called from main thread
void ANativeActivity_onCreate(ANativeActivity* activity,
                              void* savedState,
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

void* createAndroidApplication(ANativeActivity* activity,
                               void* savedState,
                               size_t savedStateSize) {
  AndroidApplication* application = new AndroidApplication(activity, savedState, savedStateSize);
#warning free application object and delete this message
  return application;
}

void onDestroy(ANativeActivity* activity) {
  Log::i(TAG, "Destroy: %p\n", activity);
}

void onStart(ANativeActivity* activity) {
  Log::i(TAG, "Start: %p\n", activity);
}

void onResume(ANativeActivity* activity) {
  Log::i(TAG, "Resume: %p\n", activity);
}

void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen) {
  Log::i(TAG, "SaveInstanceState: %p\n", activity);
  return nullptr;
}

void onPause(ANativeActivity* activity) {
  Log::i(TAG, "Pause: %p\n", activity);
}

void onStop(ANativeActivity* activity) {
  Log::i(TAG, "Stop: %p\n", activity);
}

void onConfigurationChanged(ANativeActivity* activity) {
  Log::i(TAG, "ConfigurationChanged: %p\n", activity);
}

void onLowMemory(ANativeActivity* activity) {
  Log::i(TAG, "LowMemory: %p\n", activity);
}

void onWindowFocusChanged(ANativeActivity* activity, int focused) {
  Log::i(TAG, "WindowFocusChanged: %p -- %d\n", activity, focused);
}

void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
  Log::i(TAG, "NativeWindowCreated: %p -- %p\n", activity, window);
}

void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
  Log::i(TAG, "NativeWindowDestroyed: %p -- %p\n", activity, window);
}

void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {
  Log::i(TAG, "InputQueueCreated: %p -- %p\n", activity, queue);
}

void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {
  Log::i(TAG, "InputQueueDestroyed: %p -- %p\n", activity, queue);
}