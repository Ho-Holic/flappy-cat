#ifndef FLAPPY_CAT_ANDROIDWINDOW_H
#define FLAPPY_CAT_ANDROIDWINDOW_H

// self
#include <style/Guidelines.h>
#include <core/Color.h>
#include <core/Vertices.h>
#include <core/Shape.h>
#include <core/Window.h>
#include <core/View.h>

// ndk
#include <android/native_window.h>

// egl
#include <EGL/egl.h>

// opengl
#include <GLES2/gl2.h>

// stl
#include <vector>
#include <string>
#include <core/View.h>

class AndroidWindow : public Window {
private:
  DISABLE_COPY(AndroidWindow)

public:
  AndroidWindow();

public:
  virtual void clear(const Color& color) const override;
  virtual void draw(const Shape& shape) const override;
  virtual void drawVertices(const Vertices& vertices,
                            const Transformation& transformation) const override;
  virtual void display() const override;
public:
  void setNativeWindow(ANativeWindow* window);
  bool isReady() const;
  void initialize();
  void terminate();
public:

  int32_t width() const;
  int32_t height() const;


  int32_t requestWidth() const;
  int32_t requestHeight() const;
  void resize(int32_t width, int32_t height);

private:
  void initializeOpengl();
  void initializeProgram();

private:
  static GLuint createShader(GLenum shaderType, const std::string& shaderString);
  static GLuint createProgram(const std::vector<GLuint>& shaderList);


private:
  ANativeWindow* mWindow;
  EGLDisplay mDisplay;
  EGLContext mContext;
  EGLSurface mSurface;
  EGLint mWidth;
  EGLint mHeight;
  GLuint mProgram;

private:
  View mView;
};


#endif //FLAPPY_CAT_ANDROIDWINDOW_H
