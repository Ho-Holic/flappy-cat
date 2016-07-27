#ifndef FLAPPYCAT_ANDROIDAPPLICATION_H
#define FLAPPYCAT_ANDROIDAPPLICATION_H

// ndk
#include <android/native_activity.h>

class AndroidApplication {
public:
  AndroidApplication(ANativeActivity* activity,
                     void* savedState,
                     size_t savedStateSize);
private:
  //
};


#endif //FLAPPYCAT_ANDROIDAPPLICATION_H
