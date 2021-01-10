#pragma once

#include <QWindow>
#include <core/Window.h>
#include <queue>
#include "QtEvent.h"

class QtOpenGLRender;
class QOpenGLPaintDevice;

class QtWindow : public Window, public QWindow {
public:
    QtWindow(QWindow* parent = nullptr);
    ~QtWindow();

private:
    void shouldRepaint();
    bool event(QEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
private:
    void clear(const Color& color) const override;
    void draw(const Shape& shape) const override;
    void drawVertices(const Vertices& vertices, const Transformation& transformation) const override;
    void display() const override;
private:
    void postEvent(const QtEvent& event);
    bool pollEvent(QtEvent& event);

private:
    QOpenGLContext* m_context = nullptr;
    QOpenGLPaintDevice* m_paintDevice = nullptr;
    QtOpenGLRender* m_render = nullptr;

    bool m_windowCloseRequested = false;

    std::queue<QtEvent> m_events;
};
