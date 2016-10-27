#ifndef FLAPPY_CAT_ANDROIDWINDOW_H
#define FLAPPY_CAT_ANDROIDWINDOW_H

// self
#include "style/Guidelines.h"
#include "core/Color.h"
#include "core/Vertices.h"

// ndk
#include <android/native_window.h>

// egl
#include <EGL/egl.h>

// opengl
#include <GLES2/gl2.h>

// stl
#include <vector>
#include <string>

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

public:
  void display() const;
  int32_t width() const;
  int32_t height() const;
  void drawVertices(const Vertices& vertices) const;
  void clear(const Color& color) const;
  int32_t requestWidth() const;
  int32_t requestHeight() const;
  void resize(int32_t width, int32_t height);

private:
  void initializeOpengl();
  void initializeProgram();

private:
  static GLuint createShader(GLenum shaderType, const std::string& shaderString);
  static GLuint createProgram(const std::vector<GLuint> &shaderList);


private:
  ANativeWindow* mWindow;
  EGLDisplay mDisplay;
  EGLContext mContext;
  EGLSurface mSurface;
  EGLint mWidth;
  EGLint mHeight;
  GLuint mProgram;
};


#endif //FLAPPY_CAT_ANDROIDWINDOW_H
