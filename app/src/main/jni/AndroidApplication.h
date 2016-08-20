#ifndef FLAPPY_CAT_ANDROIDAPPLICATION_H
#define FLAPPY_CAT_ANDROIDAPPLICATION_H

// ndk
#include <android/native_activity.h>
#include <android/configuration.h>

// std
#include <mutex>
#include <condition_variable>

// self
#include "Guidelines.h"
#include "AndroidConfiguration.h"
#include "AndroidLooper.h"

class AndroidApplication {
private:
  using ConfigurationDeleter = void (*)(AConfiguration*);

private:
  enum ActivityState : int8_t;

private:
  DISABLE_COPY(AndroidApplication)

public:
  AndroidApplication(ANativeActivity* activity,
                     void* savedState,
                     size_t savedStateSize);
  virtual ~AndroidApplication();

public:
  void waitForStarted();
  void requestDestruction();
  bool isRunning() const;
  bool isDestroyed() const;
  bool isDestroyRequested() const;
  ActivityState activityState() const;
  void exec();
  bool pollEvent(AndroidEvent& event);

private:
  void initialize();
  void deinitialize();
  void changeActivityStateTo(ActivityState activityState);


private:
  virtual void main() = 0; // private because launched from `exec` function

private: // android `C` callbacks
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

private:
  ANativeActivity* mActivity;
  ActivityState mActivityState;
  std::mutex mMutex;
  std::condition_variable mConditionVariable;
  bool mIsRunning;
  bool mIsDestroyed;
  AndroidConfiguration mConfiguration;
  AndroidLooper mLooper;
};

// enums

enum AndroidApplication::ActivityState : int8_t {
  InitializationActivityState,
  StartActivityState,
  ResumeActivityState,
  PauseActivityState,
  StopActivityState,

};

#endif //FLAPPY_CAT_ANDROIDAPPLICATION_H
