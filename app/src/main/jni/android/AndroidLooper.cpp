// engine
#include "AndroidLooper.hpp"

// engine
#include <core/Log.hpp>

AndroidLooper::AndroidLooper()
    : mLooper(nullptr)
    , m_inputQueue(nullptr, &AInputQueue_detachLooper)
{
    //
}

void AndroidLooper::prepare()
{

    REQUIRE(TAG, mLooper == nullptr, "must prepare looper once");

    // don't move it to constructor
    mLooper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
}

void AndroidLooper::setInputQueue(AInputQueue* inputQueue)
{

    m_inputQueue.reset(inputQueue);

    if (m_inputQueue) {
        AInputQueue_attachLooper(m_inputQueue.get(),
            mLooper, InputQueueId,
            nullptr, nullptr);
    }
}

AInputQueue* AndroidLooper::inputQueue() const
{

    return m_inputQueue.get();
}

bool AndroidLooper::pollEvent(AndroidEvent& event)
{

    int id = ALooper_pollAll(ImmediatelyWithoutBlockingTimeout,
        nullptr, nullptr, nullptr);
    switch (id) {
    case InputQueueId:
        pollFromInputQueue(event);
        break;
    case ALOOPER_POLL_TIMEOUT:
        break;
    default:
        unexpectedIdentifier(id);
        break;
    }

    bool hasAnyEvents = (id >= 0);
    return hasAnyEvents;
}

void AndroidLooper::pollFromInputQueue(AndroidEvent& event)
{

    AInputQueue* queue = m_inputQueue.get();

    AInputEvent* inputEvent = nullptr;

    int32_t nextEvent = AInputQueue_getEvent(queue, &inputEvent);

    if (nextEvent >= 0) {

        if (AInputQueue_preDispatchEvent(queue, inputEvent)) {
            return;
        }

        int32_t handled = dispatchEvent(inputEvent, event);

        AInputQueue_finishEvent(queue, inputEvent, handled);
    }
}

int32_t AndroidLooper::dispatchEvent(AInputEvent* inputEvent, AndroidEvent& event)
{

    int32_t type = AInputEvent_getType(inputEvent);

    switch (type) {
    case AINPUT_EVENT_TYPE_MOTION:
        return dispatchMotionEvent(inputEvent, event);
        break;
    case AINPUT_EVENT_TYPE_KEY:
        return dispatchKeyEvent(inputEvent, event);
        break;
    default:
        break;
    }

    return 0;
}

int32_t AndroidLooper::dispatchMotionEvent(AInputEvent* inputEvent, AndroidEvent& event)
{

    int32_t action = AMotionEvent_getAction(inputEvent);

    switch (action & AMOTION_EVENT_ACTION_MASK) {
    case AMOTION_EVENT_ACTION_DOWN:
        return dispatchTouchEvent(inputEvent, event);
        break;
    default:
        break;
    }

    return 0;
}

int32_t AndroidLooper::dispatchTouchEvent(AInputEvent* inputEvent, AndroidEvent& event)
{

    float x = AMotionEvent_getX(inputEvent, 0);
    float y = AMotionEvent_getY(inputEvent, 0);

    event.setEventType(AndroidEvent::EventType::TouchEventType);
    event.setTouchEventData(x, y);

    return 1;
}

int32_t AndroidLooper::dispatchKeyEvent(AInputEvent*, AndroidEvent&)
{
    Log::i(TAG, "Key event");

    return 0;
}

void AndroidLooper::unexpectedIdentifier(int id)
{

    Log::i(TAG, "Unexpected identifier in pollEvent = %d", id);
}
