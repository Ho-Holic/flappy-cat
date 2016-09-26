// self
#include "AndroidWindow.h"

// stl
#include <memory>

// tmp
#include <random>

// opengl
#include <GLES2/gl2.h>

AndroidWindow::AndroidWindow()
: mWindow(nullptr)
, mDisplay(EGL_NO_DISPLAY)
, mContext(EGL_NO_CONTEXT)
, mSurface(EGL_NO_SURFACE)
, mWidth(0)
, mHeight(0) {
  //
}

bool AndroidWindow::isReady() const {

  return mWindow  != nullptr
      && mDisplay != EGL_NO_DISPLAY
      && mContext != EGL_NO_CONTEXT
      && mSurface != EGL_NO_SURFACE;
}

void AndroidWindow::setNativeWindow(ANativeWindow* window) {

  mWindow = window;
}

void AndroidWindow::initialize() {

  // get display and init it
  EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

  if (display == EGL_NO_DISPLAY) {
    Log::i(TAG, "Unable to eglGetDisplay");
    return;
  }

  EGLBoolean displayState = eglInitialize(display, nullptr, nullptr);

  // choose configuration

  const EGLint configAttribs[] = {
    // can create window surfaces
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    // 32 bit color
    EGL_BLUE_SIZE,  8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE,   8,
    // enable opengl es2
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    // terminating symbol
    EGL_NONE
  };

  EGLint numConfigs = 0; // number of frame buffer configurations

  // first we get size of all configurations
  EGLBoolean chooseConfigState = eglChooseConfig(display, configAttribs,
                                                 nullptr, 0,
                                                 &numConfigs);

  REQUIRE(TAG, numConfigs != 0, "We can't have EGLConfig array with zero size!");

  // then we create array large enough to store all configs
  std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);

  // and load them
  chooseConfigState = eglChooseConfig(display, configAttribs,
                                      supportedConfigs.get(), numConfigs,
                                      &numConfigs);

  REQUIRE(TAG, numConfigs != 0, "Value of `numConfigs` must be positive");

  // match required configuration by `configAttribs`
  EGLConfig config = nullptr;

  EGLint configIndex = 0;
  for (; configIndex < numConfigs; ++configIndex) {

    EGLConfig& cfg = supportedConfigs[configIndex];

    EGLint r = 0;
    EGLint g = 0;
    EGLint b = 0;
    EGLint d = 0;

    bool hasMatch = eglGetConfigAttrib(display, cfg, EGL_RED_SIZE,   &r)
                 && eglGetConfigAttrib(display, cfg, EGL_GREEN_SIZE, &g)
                 && eglGetConfigAttrib(display, cfg, EGL_BLUE_SIZE,  &b)
                 && eglGetConfigAttrib(display, cfg, EGL_DEPTH_SIZE, &d)
                 && r == 8
                 && g == 8
                 && b == 8
                 && d == 0;

    if (hasMatch) {
      config = supportedConfigs[configIndex];
      break;
    }
  }

  // if we don't find anything choose first one
  if (configIndex == numConfigs) {
    config = supportedConfigs[0];
  }

  // EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
  // guaranteed to be accepted by ANativeWindow_setBuffersGeometry()
  // As soon as we picked a EGLConfig, we can safely reconfigure the
  // ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID.
  EGLint format = 0;

  EGLBoolean nativeVisualStatus = eglGetConfigAttrib(display, config,
                                                     EGL_NATIVE_VISUAL_ID, &format);

  EGLSurface surface = eglCreateWindowSurface(display, config, mWindow, nullptr);

  // context configuration
  EGLint contextAttribs[] = {
    // GLESv2 compatible context
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
  };

  EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);

  EGLBoolean isCurrent = eglMakeCurrent(display, surface, surface, context);

  EGLint width = 0;
  EGLint height = 0;
  eglQuerySurface(display, surface, EGL_WIDTH, &width);
  eglQuerySurface(display, surface, EGL_HEIGHT, &height);

  // setup opengl
  // Check openGL on the system
  auto opengl_info = { GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS };
  for (auto name : opengl_info) {
    auto info = glGetString(name);
    Log::i(TAG, "OpenGL Info: %s", info);
  }

  // Initialize GL state.
  glEnable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);

  // https://www.opengl.org/discussion_boards/showthread.php/179138-glShadeModel-is-depreciated-So-how-exactly-do-we-do-flat-shading-now
  // TODO: replace two lines below
  //glShadeModel(GL_SMOOTH);
  //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

  // when all done
  mDisplay = display;
  mContext = context;
  mSurface = surface;
  mWidth   = width;
  mHeight  = height;
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

void AndroidWindow::display() const {

  if ( ! isReady()) {
    return;
  }

  eglSwapBuffers(mDisplay, mSurface);
}

int32_t AndroidWindow::width() const {
  return mWidth;
}

int32_t AndroidWindow::height() const {
  return mHeight;
}

void AndroidWindow::drawRect() const {
  //
}

void AndroidWindow::clear(const AndroidColor& color) const {

  glClearColor(color.r() / 255,
               color.g() / 255,
               color.b() / 255,
               color.alpha() / 255);

  glClear(GL_COLOR_BUFFER_BIT);
  
}
