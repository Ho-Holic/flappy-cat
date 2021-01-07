#include "QtEvent.h"

#include <core/Log.h>

QtEvent::QtEvent()
: QtEvent(EmptyEventType) {
    //
}

QtEvent::QtEvent(EventType eventType)
: mEventType(eventType) {
    //
}
QtEvent::EventType QtEvent::type() const
{
    return mEventType;
}

void QtEvent::setTouchEventData(float x, float y)
{
    REQUIRE(TAG, mEventType == TouchEventType, "Must be 'MotionEventType'");

    mEventData.touchEvent.x = x;
    mEventData.touchEvent.y = y;
}
