#ifndef FLAPPY_CAT_ANDROIDAPPLICATION_H
#define FLAPPY_CAT_ANDROIDAPPLICATION_H

// ndk
#include <android/native_activity.h>
#include <android/configuration.h>

// std
#include <mutex>
#include <condition_variable>
#include <queue>

// style
#include <style/Guidelines.h>

// engine
#include "AndroidConfiguration.h"
#include "AndroidLooper.h"
#include "AndroidWindow.h"

class AndroidApplication {

private:
  enum ActivityState : int8_t;
  enum Focus: int;

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
  void postEvent(const AndroidEvent& event);
  const AndroidWindow& window() const;
  AndroidWindow& window();

private:
  void initialize();

  void changeActivityStateTo(ActivityState activityState);
  void setNativeWindow(ANativeWindow* window);
  void updateNativeWindowSize();
  void changeFocus(Focus focus);
  void setInputQueue(AInputQueue* queue);
  void reloadConfiguration();

  void terminate();

private:
  void processEvent(const AndroidEvent& event);
  void setActivityState(ActivityState activityState);
  void resizeNativeWindow(const AndroidEvent& event);
  void initializeNativeWindow(const AndroidEvent& event);
  void terminateNativeWindow(const AndroidEvent& event);
  void setInputQueue(const AndroidEvent& event);

private:
  virtual void main() = 0; // private because launched from 'AndroidApplication::exec()'

private: // android 'C' callbacks
  static void onDestroy(ANativeActivity* activity);
  static void onStart(ANativeActivity* activity);
  static void onResume(ANativeActivity* activity);
  static void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen);
  static void onPause(ANativeActivity* activity);
  static void onStop(ANativeActivity* activity);
  static void onConfigurationChanged(ANativeActivity* activity);
  static void onLowMemory(ANativeActivity* activity);
  static void onWindowFocusChanged(ANativeActivity* activity, int hasFocus);
  static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window);
  static void onNativeWindowResized(ANativeActivity* activity, ANativeWindow* window);
  static void onNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow* window);
  static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window);
  static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue);
  static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue);
  static void onContentRectChanged(ANativeActivity* activity, const ARect* rect);

private:
  ANativeActivity* mActivity;
  ActivityState mActivityState;
  std::mutex mMutex;
  std::condition_variable mConditionVariable;
  bool mIsRunning;
  bool mIsDestroyed;
  bool mIsDestroyRequested;
  AndroidConfiguration mConfiguration;
  AndroidLooper mLooper;
  AndroidWindow mWindow;
  std::queue<AndroidEvent> mEvents; // TODO: add thread safe queue
};

// enums

enum AndroidApplication::ActivityState : int8_t {
  InitializationActivityState,
  StartActivityState,
  ResumeActivityState,
  PauseActivityState,
  StopActivityState,
};

enum AndroidApplication::Focus: int {
  GainFocus,
  LostFocus,
};

#endif //FLAPPY_CAT_ANDROIDAPPLICATION_H
