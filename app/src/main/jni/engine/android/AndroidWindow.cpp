// engine
#include "AndroidWindow.h"
#include <core/Log.h>
#include <prototype/FlatTransformation.h>

// stl
#include <memory>
#include <algorithm>

enum : GLuint {
  VERTEX_POSITION_INDEX = 0,
  VERTEX_COLOR_INDEX = 1,
};

enum : GLint {
  VERTEX_POSITION_SIZE = 2,
  VERTEX_COLOR_SIZE = 4,
};

enum : GLsizei {
  VERTEX_X_INDEX,
  VERTEX_Y_INDEX,
  VERTEX_R_INDEX,
  VERTEX_G_INDEX,
  VERTEX_B_INDEX,
  VERTEX_A_INDEX,
  VERTEX_SIZE
};

AndroidWindow::AndroidWindow()
: Window()
, mIsReady(false)
, mWindow(nullptr)
, mDisplay(EGL_NO_DISPLAY)
, mContext(EGL_NO_CONTEXT)
, mSurface(EGL_NO_SURFACE)
, mWidth(0)
, mHeight(0)
, mProgram(0) {
  //
}

bool AndroidWindow::isReady() const {

  return mIsReady;
}

void AndroidWindow::setReady(bool ready) {

  mIsReady = ready;
}

void AndroidWindow::setNativeWindow(ANativeWindow* window) {

  Log::i(TAG, "Call to setNativeWindow: %p, ready: %d", window, mIsReady);

  REQUIRE(TAG, !mIsReady, "Must be inactive");

  mWindow = window;
}

ANativeWindow* AndroidWindow::nativeWindow() const {

  return mWindow;
}

void AndroidWindow::initialize() {

  Log::i(TAG, "Call to initialize: %p, ready: %d", mWindow, mIsReady);

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
    EGL_ALPHA_SIZE, 8,
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

  REQUIRE(TAG, numConfigs != 0, "Value of 'numConfigs' must be positive");

  // match required configuration by 'configAttribs'
  EGLConfig config = nullptr;

  EGLint configIndex = 0;
  for (; configIndex < numConfigs; ++configIndex) {

    EGLConfig& cfg = supportedConfigs[configIndex];

    EGLint r = 0;
    EGLint g = 0;
    EGLint b = 0;
    EGLint a = 0;
    EGLint d = 0;

    bool hasMatch = eglGetConfigAttrib(display, cfg, EGL_RED_SIZE,   &r)
                 && eglGetConfigAttrib(display, cfg, EGL_GREEN_SIZE, &g)
                 && eglGetConfigAttrib(display, cfg, EGL_BLUE_SIZE,  &b)
                 && eglGetConfigAttrib(display, cfg, EGL_ALPHA_SIZE, &a)
                 && eglGetConfigAttrib(display, cfg, EGL_DEPTH_SIZE, &d)
                 && r == 8
                 && g == 8
                 && b == 8
                 && a == 8
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

  /** TODO: check this bunch of unused variables
   *
   *  Decide do we need to process return values or just can discard them?
   */
  UNUSED(displayState);
  UNUSED(chooseConfigState);
  UNUSED(nativeVisualStatus);
  UNUSED(isCurrent);

  // when all done
  mDisplay = display;
  mContext = context;
  mSurface = surface;

  // set window size
  mWidth = requestWidth();
  mHeight = requestHeight();

  // deal with opengl now
  initializeOpengl();

  mIsReady = true;

}

void AndroidWindow::terminate() {

  Log::i(TAG, "Call to terminate: %p, ready: %d", mWindow, mIsReady);

  REQUIRE(TAG, !mIsReady, "Must be inactive");

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

void AndroidWindow::initializeOpengl() {

  // Check openGL on the system
  std::initializer_list<GLenum> opengl_info = {
    GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS,
    GL_SHADING_LANGUAGE_VERSION
  };

  for (GLenum name : opengl_info) {

    const GLubyte* info = glGetString(name);
    Log::i(TAG, "OpenGL Info: %s", info);
  }

  // Initialize GL state.
  glEnable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  initializeProgram();
}

void AndroidWindow::initializeProgram() {

    static std::string strVertexShader(R"(
      attribute vec4 a_position;
      attribute vec4 a_color;
      varying vec4 v_color;
      void main() {
        v_color = a_color;
        gl_Position = a_position;
      }
    )");

    static std::string strFragmentShader(R"(
      precision mediump float;
      varying vec4 v_color;
      void main() {
        gl_FragColor = v_color;
      }
    )");

  std::vector<GLuint> shaderList = {
    createShader(GL_VERTEX_SHADER, strVertexShader),
    createShader(GL_FRAGMENT_SHADER, strFragmentShader)
  };

  mProgram = createProgram(shaderList);

  std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}

GLuint AndroidWindow::createShader(GLenum shaderType, const std::string& shaderString) {

  GLuint shader = glCreateShader(shaderType);

  const char* shaderStringData = shaderString.c_str();
  glShaderSource(shader, 1, &shaderStringData, nullptr);
  glCompileShader(shader);

  GLint compiled = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if (compiled == GL_FALSE) {

    GLint infoLogLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 1) {

      std::unique_ptr<GLchar[]> infoLogString(new GLchar[infoLogLength]);
      glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLogString.get());

      Log::i(TAG, "Error compiling shader:\n%s\n", infoLogString.get());
    }
  }

  return shader;
}

GLuint AndroidWindow::createProgram(const std::vector<GLuint>& shaderList) {

  GLuint program = glCreateProgram();

  for (GLuint shader : shaderList) {

    glAttachShader(program, shader);
  }

  glBindAttribLocation(program, VERTEX_POSITION_INDEX, "a_position");
  glBindAttribLocation(program, VERTEX_COLOR_INDEX, "a_color");

  glLinkProgram(program);

  REQUIRE(TAG, glGetAttribLocation(program, "a_position") == VERTEX_POSITION_INDEX,
          "Must be correct");

  REQUIRE(TAG, glGetAttribLocation(program, "a_color") == VERTEX_COLOR_INDEX,
          "Must be correct");

  GLint linked = GL_FALSE;
  glGetProgramiv (program, GL_LINK_STATUS, &linked);

  if (linked == GL_FALSE) {

    GLint infoLogLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 1) {

      std::unique_ptr<GLchar[]> infoLogString(new GLchar[infoLogLength]);
      glGetProgramInfoLog(program, infoLogLength, NULL, infoLogString.get());

      Log::i(TAG, "Linker failure: %s\n", infoLogString.get());
    }
  }

  for (GLuint shader : shaderList) {

    glDetachShader(program, shader);
  }

  return program;
}

void AndroidWindow::display() const {

  eglSwapBuffers(mDisplay, mSurface);
}

int32_t AndroidWindow::width() const {

  return mWidth;
}

int32_t AndroidWindow::height() const {

  return mHeight;
}

int32_t AndroidWindow::requestWidth() const {
  
  return ANativeWindow_getWidth(mWindow);
}

int32_t AndroidWindow::requestHeight() const {

  return ANativeWindow_getHeight(mWindow);
}

void AndroidWindow::drawVertices(const Vertices& vertices,
                                 const Transformation& transformation) const {

  std::size_t verticesDataSize = vertices.size() * VERTEX_SIZE;

  std::unique_ptr<GLfloat[]> verticesData(new GLfloat[verticesDataSize]);

  for (std::size_t i = 0; i < vertices.size(); ++i) {

    std::size_t stride = i * VERTEX_SIZE;

    // TODO: add transformation rotation/origin later

    verticesData[VERTEX_X_INDEX + stride] = (2.f / transformation.position().x())
                                            * vertices[i].position().x()
                                            * transformation.scale().x();

    verticesData[VERTEX_Y_INDEX + stride] = (2.f / transformation.position().y())
                                            * vertices[i].position().y()
                                            * transformation.scale().y();

    verticesData[VERTEX_R_INDEX + stride] = vertices[i].color().r() / 255.f;
    verticesData[VERTEX_G_INDEX + stride] = vertices[i].color().g() / 255.f;
    verticesData[VERTEX_B_INDEX + stride] = vertices[i].color().b() / 255.f;
    verticesData[VERTEX_A_INDEX + stride] = vertices[i].color().alpha() / 255.f;

  }

  glVertexAttribPointer(VERTEX_POSITION_INDEX, VERTEX_POSITION_SIZE, GL_FLOAT, GL_FALSE,
                        VERTEX_SIZE * sizeof(GLfloat), &verticesData[VERTEX_X_INDEX]);

  glVertexAttribPointer(VERTEX_COLOR_INDEX, VERTEX_COLOR_SIZE, GL_FLOAT, GL_FALSE,
                        VERTEX_SIZE * sizeof(GLfloat), &verticesData[VERTEX_R_INDEX]);

  glEnableVertexAttribArray(VERTEX_POSITION_INDEX);
  glEnableVertexAttribArray(VERTEX_COLOR_INDEX);

  glUseProgram(mProgram);

  glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(vertices.size()));


  glDisableVertexAttribArray(VERTEX_POSITION_INDEX);
  glDisableVertexAttribArray(VERTEX_COLOR_INDEX);

  glUseProgram(0);

}

void AndroidWindow::clear(const Color& color) const {

  glClearColor(color.r()     / 255.f,
               color.g()     / 255.f,
               color.b()     / 255.f,
               color.alpha() / 255.f);

  glClear(GL_COLOR_BUFFER_BIT);

}

void AndroidWindow::resize(int32_t width, int32_t height) {

  Log::i(TAG, "New size (%d - %d)\n", width, height);

  mWidth = width;
  mHeight = height;

  view().setPosition(Position(static_cast<Position::value_type>(mWidth),
                              static_cast<Position::value_type>(mHeight)));

  // Set the viewport
  glViewport(0, 0, mWidth, mHeight);
}

void AndroidWindow::draw(const Shape& shape) const {

  shape.render().drawOn(*this, view());
}




