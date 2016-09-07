// self
#include "AndroidWindow.h"

AndroidWindow::AndroidWindow()
: mWindow(nullptr)
, mDisplay(EGL_NO_DISPLAY)
, mContext(EGL_NO_CONTEXT)
, mSurface(EGL_NO_SURFACE) {
  //
}

bool AndroidWindow::isReady() const {

  return mWindow != nullptr;
}

void AndroidWindow::setNativeWindow(ANativeWindow* window) {

  mWindow = window;
}

void AndroidWindow::initialize() {

  EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);


  EGLBoolean displayState = eglInitialize(display, nullptr, nullptr);

  // choose configuration
  // `EGL_NONE` is used like null terminating symbol in C-string don't forget it
  const EGLint attribs[] = {
    EGL_SURFACE_TYPE,
    EGL_WINDOW_BIT,
    EGL_BLUE_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE, 8,
    EGL_NONE
  };

  EGLint numConfigs; // number of frame buffer configurations

  EGLBoolean chooseConfigState = eglChooseConfig(display, attribs,
                                                 nullptr, 0,
                                                 &numConfigs);

  // when all done
  mDisplay = display;
}

void AndroidWindow::terminate() {

  if (mDisplay != EGL_NO_DISPLAY) {

    eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    if (mContext != EGL_NO_CONTEXT) {
      eglDestroyContext(mDisplay, mContext);
    }

    if (mSurface != EGL_NO_SURFACE) {
      eglDestroySurface(mDisplay, mSurface);
    }

    eglTerminate(mDisplay);
  }

  mDisplay = EGL_NO_DISPLAY;
  mContext = EGL_NO_CONTEXT;
  mSurface = EGL_NO_SURFACE;
}
