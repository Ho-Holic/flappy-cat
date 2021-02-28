#pragma once

// stl
#include <cstdint>

// engine
#include "QtEventData.hpp"

// style
#include "style/Guidelines.hpp"

class QtEvent {
public:
    enum EventType : int8_t;

    QtEvent();
    QtEvent(EventType eventType);
    EventType type() const;

    void setTouchEventData(float x, float y);

private:
    EventType m_eventType;
    QtEventData m_eventData;
};

enum QtEvent::EventType : int8_t {
    EmptyEventType,
    TouchEventType,
};
