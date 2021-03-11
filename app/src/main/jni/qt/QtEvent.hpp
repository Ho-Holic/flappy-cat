#pragma once

#include "QtEventData.hpp"
#include "style/Guidelines.hpp"
#include <cstdint>

class QtEvent {
public:
    enum EventType : int8_t;

    QtEvent();
    QtEvent(EventType eventType);
    EventType type() const;

    void setTouchEventData(float x, float y);
    void setResizeEventData(int width, int height);

    const QtTouchEvent& touchEvent() const;

private:
    EventType m_eventType;
    QtEventData m_eventData;
};

enum QtEvent::EventType : int8_t {
    EmptyEventType,
    TouchEventType,
    ResizedEventType,
};
