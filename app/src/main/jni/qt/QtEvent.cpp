#include "QtEvent.hpp"
#include <core/Log.hpp>

QtEvent::QtEvent()
    : QtEvent(EmptyEventType)
{
    //
}

QtEvent::QtEvent(EventType eventType)
    : m_eventType(eventType)
{
    //
}
QtEvent::EventType QtEvent::type() const
{
    return m_eventType;
}

void QtEvent::setTouchEventData(float x, float y)
{
    REQUIRE(TAG, m_eventType == TouchEventType, "Must be 'MotionEventType'");

    m_eventData.touchEvent.x = x;
    m_eventData.touchEvent.y = y;
}

void QtEvent::setResizeEventData(int width, int height)
{

    REQUIRE(TAG, m_eventType == ResizedEventType, "Must be 'ResizedEventType'");

    m_eventData.resizeEvent.width = width;
    m_eventData.resizeEvent.height = height;
}

const QtTouchEvent& QtEvent::touchEvent() const
{
    REQUIRE(TAG, m_eventType == TouchEventType, "Must be 'MotionEventType'");

    return m_eventData.touchEvent;
}
