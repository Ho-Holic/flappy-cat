#ifndef FLAPPY_CAT_ANDROIDEVENTDATA_H
#define FLAPPY_CAT_ANDROIDEVENTDATA_H


// ndk
#include <android/native_activity.h>

struct AndroidTouchEvent {

  float x;
  float y;
};

struct AndroidResizeEvent {
  int32_t width;
  int32_t height;
};

struct AndroidNativeWindowEvent {
  ANativeWindow* pendingWindow;
};

union AndroidEventData {

  AndroidTouchEvent  touchEvent;
  AndroidResizeEvent resizeEvent;
  AndroidNativeWindowEvent nativeWindowEvent;
};

#endif //FLAPPY_CAT_ANDROIDEVENTDATA_H
