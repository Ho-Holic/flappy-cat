#ifndef FLAPPYCAT_ANDROIDAPPLICATION_H
#define FLAPPYCAT_ANDROIDAPPLICATION_H

// ndk
#include <android/native_activity.h>

// std
#include <mutex>
#include <condition_variable>

class AndroidApplication {
public:
  AndroidApplication(ANativeActivity* activity,
                     void* savedState,
                     size_t savedStateSize);
public:
  void exec();
private:
  std::mutex mMutex;
  std::condition_variable mConditionalVariable;
};


#endif //FLAPPYCAT_ANDROIDAPPLICATION_H
