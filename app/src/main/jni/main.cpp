// ndk
#include <android/native_activity.h>

// self
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

void ANativeActivity_onCreate(ANativeActivity* activity,
                              void* savedState,
                              size_t savedStateSize) {

  Log::v(TAG, "Creating activity: %p\n", activity);
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
  //activity->instance = android_app_create(activity, savedState, savedStateSize);
}

void onDestroy(ANativeActivity* activity) {
  //LOGI("Destroy: %p\n", activity);
}

void onStart(ANativeActivity* activity) {
  //LOGI("Start: %p\n", activity);
}

void onResume(ANativeActivity* activity) {
  //LOGI("Resume: %p\n", activity);
}

void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen) {
  //LOGI("SaveInstanceState: %p\n", activity);
  return nullptr;
}

void onPause(ANativeActivity* activity) {
  //LOGI("Pause: %p\n", activity);
}

void onStop(ANativeActivity* activity) {
  //LOGI("Stop: %p\n", activity);
}

void onConfigurationChanged(ANativeActivity* activity) {
  //LOGI("ConfigurationChanged: %p\n", activity);
}

void onLowMemory(ANativeActivity* activity) {
  //LOGI("LowMemory: %p\n", activity);
}

void onWindowFocusChanged(ANativeActivity* activity, int focused) {
  //LOGI("WindowFocusChanged: %p -- %d\n", activity, focused);
}

void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
  //LOGI("NativeWindowCreated: %p -- %p\n", activity, window);
}

void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
  //LOGI("NativeWindowDestroyed: %p -- %p\n", activity, window);
}

void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {
  //LOGI("InputQueueCreated: %p -- %p\n", activity, queue);
}

void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {
  //LOGI("InputQueueDestroyed: %p -- %p\n", activity, queue);
}