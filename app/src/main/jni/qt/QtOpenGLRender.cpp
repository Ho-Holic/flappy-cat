#include "QtOpenGLRender.hpp"
#include <core/Log.hpp>
#include <memory>

enum : GLuint {
    AttributePosition,
    AttributeColor,
};

enum : GLsizei {
    AttributePositionX,
    AttributePositionY,
    AttributeColorR,
    AttributeColorG,
    AttributeColorB,
    AttributeColorA,
    AttributeSize,
};

enum : GLint {
    AttributePositionSize = 2,
    AttributeColorSize = 4,
};

static_assert(AttributeSize == AttributePositionSize + AttributeColorSize, "invalid layout");

QtOpenGLRender::QtOpenGLRender(QOpenGLContext* context)
    : QOpenGLFunctions(context)
{
    //
}

void QtOpenGLRender::init()
{
    initializeOpenGLFunctions(); // before any use of `gl*` prefixed functions

    static std::string vertexShader(R"(
      attribute vec4 a_position;
      attribute vec4 a_color;
      varying vec4 v_color;
      void main() {
        v_color = a_color;
        gl_Position = a_position;
      }
    )");

    static std::string pixelShader(R"(

      varying vec4 v_color;
      void main() {
        gl_FragColor = v_color;
      }
    )");

    std::vector<GLuint> shaders = {
        createShader(GL_VERTEX_SHADER, vertexShader.c_str()),
        createShader(GL_FRAGMENT_SHADER, pixelShader.c_str()),
    };

    m_program = createProgram(shaders);

    for (auto shader : shaders) {
        glDeleteShader(shader);
    }
}

void QtOpenGLRender::requestSwapBuffers()
{
    m_swapBuffersRequested = true;
}

bool QtOpenGLRender::isSwapBuffersRequested() const
{
    return m_swapBuffersRequested;
}

void QtOpenGLRender::clearQueue()
{
    m_layersBackBuffer.clear();
}

void QtOpenGLRender::enqueue(int layerIndex, const Vertices& vertices, const Transformation& transformation)
{
    Polygon polygon;

    for (std::size_t i = 0; i < vertices.size(); ++i) {

        auto x = (2.f / transformation.position().x()) * vertices[i].position().x() * transformation.scale().x();
        auto y = (2.f / transformation.position().y()) * vertices[i].position().y() * transformation.scale().y();

        polygon.vertices << Vertex(vec2(x, y), vertices[i].color());
    }

    m_layersBackBuffer[layerIndex].push_back(polygon);
}

void QtOpenGLRender::render()
{
    if (m_swapBuffersRequested) {
        m_layersFrontBuffer.swap(m_layersBackBuffer);
        m_swapBuffersRequested = false;
    }

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_program);

    for (auto layer : m_layersFrontBuffer) {

        const auto& polygons = layer.second;

        for (const auto& polygon : polygons) {

            auto bufferSize = polygon.vertices.size() * AttributeSize;
            std::unique_ptr<GLfloat[]> buffer(new GLfloat[bufferSize]);

            for (std::size_t i = 0; i < polygon.vertices.size(); ++i) {

                std::size_t stride = i * AttributeSize;

                buffer[AttributePositionX + stride] = polygon.vertices[i].position().x();
                buffer[AttributePositionY + stride] = polygon.vertices[i].position().y();

                buffer[AttributeColorR + stride] = polygon.vertices[i].color().r() / 255.f;
                buffer[AttributeColorG + stride] = polygon.vertices[i].color().g() / 255.f;
                buffer[AttributeColorB + stride] = polygon.vertices[i].color().b() / 255.f;
                buffer[AttributeColorA + stride] = polygon.vertices[i].color().alpha() / 255.f;
            }

            glVertexAttribPointer(AttributePosition, AttributePositionSize, GL_FLOAT, GL_FALSE, AttributeSize * sizeof(GLfloat), &buffer[AttributePositionX]);
            glVertexAttribPointer(AttributeColor, AttributeColorSize, GL_FLOAT, GL_FALSE, AttributeSize * sizeof(GLfloat), &buffer[AttributeColorR]);

            glEnableVertexAttribArray(AttributePosition);
            glEnableVertexAttribArray(AttributeColor);

            glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(polygon.vertices.size()));

            glDisableVertexAttribArray(AttributePosition);
            glDisableVertexAttribArray(AttributeColor);
        }
    }

    glUseProgram(0);
}

GLuint QtOpenGLRender::createShader(GLenum shaderType, const char* shaderCode)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (compiled == GL_FALSE) {
        GLint errorStringLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorStringLength);

        if (errorStringLength > 1) {
            std::unique_ptr<GLchar[]> errorString(new GLchar[errorStringLength]);
            glGetShaderInfoLog(shader, errorStringLength, nullptr, errorString.get());

            Log::i("QtOpenGLRender", "Error compiling shader: ", errorString.get());
        }
    }

    return shader;
}

GLuint QtOpenGLRender::createProgram(const std::vector<GLuint>& shaders)
{

    GLuint program = glCreateProgram();

    for (auto shader : shaders) {
        glAttachShader(program, shader);
    }    

    {
        glBindAttribLocation(program, AttributePosition, "a_position_modelspace");
        glBindAttribLocation(program, AttributeColor, "a_color_modelspace");
        glLinkProgram(program);

        GLint linked = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);

        if (linked == GL_FALSE) {

            GLint errorStringLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &errorStringLength);

            if (errorStringLength > 1) {

                std::unique_ptr<GLchar[]> errorString(new GLchar[errorStringLength]);
                glGetProgramInfoLog(program, errorStringLength, NULL, errorString.get());

                Log::i("QtOpenGLRender", "Error linking program: ", errorString.get());
            }
        }
    }

    for (auto shader : shaders) {
        glDetachShader(program, shader);
    }

    return program;
}
