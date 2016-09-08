#ifndef FLAPPY_CAT_ANDROIDWINDOW_H
#define FLAPPY_CAT_ANDROIDWINDOW_H

// self
#include "Guidelines.h"

// ndk
#include <android/native_window.h>

// egl
#include <EGL/egl.h>

class AndroidWindow {
private:
  DISABLE_COPY(AndroidWindow)
public:
  AndroidWindow();
public:
  void setNativeWindow(ANativeWindow* window);
  bool isReady() const;
  void initialize();
  void terminate();
  void draw() const;
private:
  ANativeWindow* mWindow;
  EGLDisplay mDisplay;
  EGLContext mContext;
  EGLSurface mSurface;
  EGLint mWidth;
  EGLint mHeight;
};


#endif //FLAPPY_CAT_ANDROIDWINDOW_H
