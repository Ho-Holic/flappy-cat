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
  DISABLE_COPY(AndroidApplication)

public:
  AndroidApplication(ANativeActivity* activity,
                     void* savedState,
                     size_t savedStateSize);
public:
  void waitForStarted();
  void requestDestruction();
  bool isRunning() const;
  bool isDestroyed() const;
  void exec();

private:
  void initialize();
  void deinitialize();

private:
  ANativeActivity* mActivity;
  std::mutex mMutex;
  std::condition_variable mConditionVariable;
  bool mIsRunning;
  bool mIsDestroyed;
  AndroidConfiguration mConfiguration;
  AndroidLooper mLooper;
};


#endif //FLAPPY_CAT_ANDROIDAPPLICATION_H
