#ifndef FLAPPYCAT_ANDROIDAPPLICATION_H
#define FLAPPYCAT_ANDROIDAPPLICATION_H

// ndk
#include <android/native_activity.h>

// std
#include <mutex>
#include <condition_variable>

// self
#include "macro.h"

class AndroidApplication {
private:
  DISABLE_COPY(AndroidApplication)
public:
  AndroidApplication(ANativeActivity* activity,
                     void* savedState,
                     size_t savedStateSize);
public:
  void exec();
  void waitForStarted();
  bool isRunning() const;

private:
  ANativeActivity* mActivity;
  std::mutex mMutex;
  std::condition_variable mConditionVariable;
  bool mIsRunning;
};


#endif //FLAPPYCAT_ANDROIDAPPLICATION_H
