// self
#include "AndroidWindow.h"

AndroidWindow::AndroidWindow()
: mWindow(nullptr) {
  //
}

bool AndroidWindow::isReady() const {

  return mWindow != nullptr;
}

void AndroidWindow::setNativeWindow(ANativeWindow* window) {

  mWindow = window;
}

void AndroidWindow::initialize() {
  //
}

void AndroidWindow::terminate() {
  //
}
