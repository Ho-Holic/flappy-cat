#pragma once

// engine
#include <core/Color.hpp>
#include <core/Shape.hpp>
#include <core/Vertices.hpp>
#include <core/View.hpp>
#include <core/Window.hpp>

// style
#include <style/Guidelines.hpp>

// ndk
#include <android/native_window.h>

// egl
#include <EGL/egl.h>

// opengl
#include <GLES2/gl2.h>

// stl
#include <string>
#include <vector>

class AndroidWindow : public Window {
private:
    AndroidWindow(const AndroidWindow&) = delete;
    AndroidWindow& operator=(const AndroidWindow&) = delete;

public:
    AndroidWindow();

public:
    void clear(const Color& color) const override;
    void draw(const Shape& shape) const override;
    virtual void drawVertices(const Vertices& vertices,
        const Transformation& transformation) const override;
    void display() const override;

public:
    void setNativeWindow(ANativeWindow* window);
    ANativeWindow* nativeWindow() const;
    void setReady(bool ready);
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
    bool m_isReady;
    ANativeWindow* m_window;
    EGLDisplay m_display;
    EGLContext m_context;
    EGLSurface m_surface;
    EGLint m_width;
    EGLint m_height;
    GLuint m_program;
};
