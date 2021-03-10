#pragma once

#include "core/Transformation.hpp"
#include "core/Vertices.hpp"
#include <QOpenGLFunctions>
#include <map>
#include <vector>

struct Polygon {
    Vertices vertices;
};

class QOpenGLContext;

class QtOpenGLRender : public QOpenGLFunctions {
public:
    QtOpenGLRender(QOpenGLContext* context);
    void init();
    void requestSwapBuffers();
    bool isSwapBuffersRequested() const;

public:
    void enqueue(int layerIndex, const Vertices& vertices, const mat3& transformMatrix);
    void render();
    void clearQueue();

private:
    GLuint createShader(GLenum shaderType, const char* shaderCode);
    GLuint createProgram(const std::vector<GLuint>& shaders);

private:
    bool m_swapBuffersRequested = false;
    std::map<int, std::vector<Polygon>> m_layersFrontBuffer;
    std::map<int, std::vector<Polygon>> m_layersBackBuffer;

    GLuint m_program = 0;
};
