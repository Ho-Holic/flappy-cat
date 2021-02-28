// engine
#include "AndroidEvent.hpp"

// engine
#include <core/Log.hpp>

AndroidEvent::AndroidEvent()
    : AndroidEvent(EmptyEventType)
{
    //
}

AndroidEvent::AndroidEvent(EventType eventType)
    : m_eventType(eventType)
{
    //
}

AndroidEvent::EventType AndroidEvent::type() const
{

    return m_eventType;
}

void AndroidEvent::setEventType(EventType eventType)
{

    m_eventType = eventType;
}

void AndroidEvent::setTouchEventData(float x, float y)
{

    REQUIRE(TAG, m_eventType == TouchEventType, "Must be 'MotionEventType'");

    m_eventData.touchEvent.x = x;
    m_eventData.touchEvent.y = y;
}

const AndroidTouchEvent& AndroidEvent::touchEvent() const
{

    REQUIRE(TAG, m_eventType == TouchEventType, "Must be 'MotionEventType'");

    return m_eventData.touchEvent;
}

void AndroidEvent::setResizeEventData(int32_t width, int32_t height)
{

    REQUIRE(TAG, m_eventType == ResizedEventType, "Must be 'ResizedEventType'");

    m_eventData.resizeEvent.width = width;
    m_eventData.resizeEvent.height = height;
}

void AndroidEvent::setNativeWindowEventData(ANativeWindow* pendingWindow)
{

    REQUIRE(TAG, m_eventType == NativeWindowCreatedEventType || m_eventType == NativeWindowDestroyedEventType,
        "Must be 'NativeWindowCreatedEventType' or 'NativeWindowDestroyedEventType'");

    m_eventData.nativeWindowEvent.pendingWindow = pendingWindow;
}

void AndroidEvent::setInputQueueEventData(AInputQueue* pendingQueue)
{

    REQUIRE(TAG, m_eventType == InputQueueCreatedEventType || m_eventType == InputQueueDestroyedEventType,
        "Must be 'InputQueueCreatedEventType' or 'InputQueueDestroyedEventType'");

    m_eventData.inputQueueEvent.pendingQueue = pendingQueue;
}

void AndroidEvent::setEventLoopEventData(bool windowReady)
{
    REQUIRE(TAG, m_eventType == EventLoopEventType, "Must be 'EventLoopEventType'");

    m_eventData.eventLoopEvent.windowReady = windowReady;
}

const AndroidResizeEvent& AndroidEvent::resizeEvent() const
{

    REQUIRE(TAG, m_eventType == ResizedEventType, "Must be 'ResizedEventType'");

    return m_eventData.resizeEvent;
}

const AndroidNativeWindowEvent& AndroidEvent::nativeWindowEvent() const
{

    REQUIRE(TAG, m_eventType == NativeWindowCreatedEventType || m_eventType == NativeWindowDestroyedEventType,
        "Must be 'NativeWindowCreatedEventType' or 'NativeWindowDestroyedEventType'");

    return m_eventData.nativeWindowEvent;
}

const AndroidInputQueueEvent& AndroidEvent::inputQueueEvent() const
{

    REQUIRE(TAG, m_eventType == InputQueueCreatedEventType || m_eventType == InputQueueDestroyedEventType,
        "Must be 'InputQueueCreatedEventType' or 'InputQueueDestroyedEventType'");

    return m_eventData.inputQueueEvent;
}

const AndroidEventLoopEvent& AndroidEvent::eventLoopEvent() const
{

    REQUIRE(TAG, m_eventType == EventLoopEventType, "Must be 'EventLoopEventType'");

    return m_eventData.eventLoopEvent;
}
