#pragma once

#include <QWindow>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>

class QtWindow : public QWindow, protected QOpenGLFunctions
{
public:
    QtWindow(QWindow* parent = nullptr);
    ~QtWindow();
private:
    bool event(QEvent* event) override;
    void exposeEvent(QExposeEvent*) override;
    void render();
private:
    QOpenGLContext m_context;
    QOpenGLPaintDevice* m_paintDevice;
};
