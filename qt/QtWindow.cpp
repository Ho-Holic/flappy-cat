#include "QtWindow.hpp"
#include <QEvent>
#include <QGuiApplication>

QtWindow::QtWindow(QWindow *parent)
    : QWindow(parent)
    , m_context()
    , m_paintDevice(nullptr)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);

    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);

    m_context.setFormat(format);
    m_context.create();
}

QtWindow::~QtWindow()
{
    delete m_paintDevice;
}

void QtWindow::render()
{
    m_context.makeCurrent(this);

    if (!m_paintDevice) {
        m_paintDevice = new QOpenGLPaintDevice();
    }

    if (m_paintDevice->size() != size()) {
        m_paintDevice->setSize(size());
    }

    QOpenGLFunctions* f = m_context.functions();
    f->glClearColor(1.f, 0.f, 0.f, 1.f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_context.swapBuffers(this);

    QGuiApplication::postEvent(this, new QEvent(QEvent::UpdateRequest)); // request next update frame
}

void QtWindow::exposeEvent(QExposeEvent*) {
    if (isExposed()) {
        render();
    } else {
        // stop rendering, window is hidden
    }
}

bool QtWindow::event(QEvent* event) {
    if (event->type() == QEvent::UpdateRequest) {
        render();
        return true;
    }
    return QWindow::event(event);
}
