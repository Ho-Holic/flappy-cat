#pragma once

#include <QOpenGLFunctions>
#include <map>
#include <vector>

// engine
#include "core/Vertices.h"
#include "core/Transformation.h"

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
    void enqueue(int layerIndex, const Vertices &vertices, const Transformation &transformation);
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
