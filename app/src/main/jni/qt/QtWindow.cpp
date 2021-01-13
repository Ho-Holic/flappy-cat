#include "QtWindow.hpp"
#include "QtOpenGLRender.hpp"
#include <QEvent>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QOpenGLPaintDevice>
#include <QTimer>
#include <thread>

// engine
#include "FlappyCatClock.hpp"
#include "FlappyCatGame.hpp"
#include <core/Clock.hpp>

QtWindow::QtWindow(QWindow* parent)
    : QWindow(parent)
{
    auto loopTimer = new QTimer(this);
    loopTimer->setTimerType(Qt::PreciseTimer);
    connect(loopTimer, &QTimer::timeout, this, &QtWindow::shouldRepaint);

    int timePerFrameMs = std::chrono::duration_cast<std::chrono::milliseconds>(FrameDuration { 1 }).count();
    loopTimer->start(timePerFrameMs);
}

QtWindow::~QtWindow()
{
    delete m_render;
    delete m_paintDevice;
    delete m_context;
}

void QtWindow::shouldRepaint()
{
    if (!isExposed()) {
        return;
    }

    if (!m_context) {

        QSurfaceFormat format;
        format.setDepthBufferSize(24);
        format.setStencilBufferSize(8);

        setSurfaceType(QWindow::OpenGLSurface);
        setFormat(format);

        m_context = new QOpenGLContext(this);
        m_context->setFormat(format);
        m_context->create();
        m_context->makeCurrent(this);

        m_paintDevice = new QOpenGLPaintDevice();

        m_render = new QtOpenGLRender(m_context);
        m_render->init();

        // run game thread
        {
            std::thread gameModelThread([this]() -> void {
                using std::chrono::duration_cast;

                constexpr auto timePerFrame = FrameDuration { 1 };

                auto startTime = Clock::now();
                auto timeSinceLastUpdate = Clock::duration { 0 };

                auto measurement = 0.f;
                auto smoothing = 0.9f;

                FlappyCatGame game;
                float windowHeight = static_cast<float>(size().height());
                float cameraHeight = game.cameraSize().y();
                float scale = windowHeight / cameraHeight;
                view().setScale(Position(scale, scale));

                while (!m_windowCloseRequested) {
                    auto now = Clock::now();
                    auto elapsedTime = now - startTime;

                    // fps counter
                    {
                        measurement = (measurement * smoothing) + duration_cast<GameSecond>(elapsedTime).count() * (1.f - smoothing);
                        game.setFpsCounter(static_cast<size_t>(1.f / measurement));
                    }

                    startTime = now;
                    timeSinceLastUpdate += elapsedTime;

                    while (timeSinceLastUpdate > timePerFrame) {

                        timeSinceLastUpdate = timeSinceLastUpdate - duration_cast<decltype(timeSinceLastUpdate)>(timePerFrame);

                        Event event;
                        while (pollEvent(event)) {
                            game.processEvent(event);
                        }

                        game.update(timePerFrame);
                    }

                    if (!m_render->isSwapBuffersRequested()) {
                        m_render->clearQueue();
                        game.render(*this);
                        m_render->requestSwapBuffers();
                    }
                }
            });

            gameModelThread.detach();
        }
    }

    if (m_paintDevice->size() != size()) {

        m_paintDevice->setSize(size());
        view().setPosition(Position(static_cast<float>(size().width()), static_cast<float>(size().height())));
    }

    m_context->makeCurrent(this);
    m_render->render();
    m_context->swapBuffers(this);
}

bool QtWindow::event(QEvent* event)
{
    if (event->type() == QEvent::Close) {
        m_windowCloseRequested = true;
    }
    return QWindow::event(event);
}

void QtWindow::mouseReleaseEvent(QMouseEvent*)
{
    using EventType = QtEvent::EventType;

    QtEvent event(EventType::TouchEventType);

    event.setTouchEventData(0.f, 0.f);

    this->postEvent(event);
}

void QtWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space) {
        using EventType = QtEvent::EventType;

        QtEvent event(EventType::TouchEventType);

        event.setTouchEventData(0.f, 0.f);

        this->postEvent(event);
    }
}

void QtWindow::clear(const Color& color) const
{
    // do nothing in qt build
}

void QtWindow::draw(const Shape& shape) const
{
    shape.render().drawOn(*this, view());
}

void QtWindow::drawVertices(const Vertices& vertices, const Transformation& transformation) const
{
    m_render->enqueue(0, vertices, transformation);
}

void QtWindow::display() const
{
    // do nothing in qt build
}

void QtWindow::postEvent(const QtEvent& event)
{

    m_events.push(event);
}

bool QtWindow::pollEvent(QtEvent& event)
{
    if (!m_events.empty()) {

        event = m_events.front();
        m_events.pop();

        return true;
    }

    return false;
}
