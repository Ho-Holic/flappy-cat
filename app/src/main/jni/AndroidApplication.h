#ifndef FLAPPYCAT_ANDROIDAPPLICATION_H
#define FLAPPYCAT_ANDROIDAPPLICATION_H

// ndk
#include <android/native_activity.h>
#include <android/configuration.h>

// std
#include <mutex>
#include <condition_variable>
#include <memory>

// self
#include "macro.h"

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
  bool isRunning() const;
  void exec();

private:
  void initialize();

private:
  ANativeActivity* mActivity;
  std::mutex mMutex;
  std::condition_variable mConditionVariable;
  bool mIsRunning;
  std::unique_ptr<AConfiguration, ConfigurationDeleter> mConfiguration;
};


#endif //FLAPPYCAT_ANDROIDAPPLICATION_H
