#pragma once

// stl
#include <cstdint>

// engine
#include "QtEventData.h"

// style
#include "style/Guidelines.h"

class QtEvent {
public:
    enum EventType : int8_t;

    QtEvent();
    QtEvent(EventType eventType);
    EventType type() const;

    void setTouchEventData(float x, float y);

private:
    EventType mEventType;
    QtEventData mEventData;
};

enum QtEvent::EventType : int8_t {
    EmptyEventType,
    TouchEventType,
};
