#ifndef FLAPPY_CAT_ANDROIDWINDOW_H
#define FLAPPY_CAT_ANDROIDWINDOW_H

// self
#include "Guidelines.h"

// ndk
#include <android/native_window.h>

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
private:
  ANativeWindow* mWindow;
};


#endif //FLAPPY_CAT_ANDROIDWINDOW_H
