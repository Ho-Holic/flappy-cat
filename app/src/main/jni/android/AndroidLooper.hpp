#pragma once

// ndk
#include <android/input.h>
#include <android/looper.h>

// style
#include "style/Guidelines.hpp"

// engine
#include "AndroidEvent.hpp"

// stl
#include <cstdint>
#include <memory>

class AndroidLooper {
private:
    AndroidLooper(const AndroidLooper&) = delete;
    AndroidLooper& operator=(const AndroidLooper&) = delete;

public:
    enum Id : int;
    enum Timeout : int;

public:
    using DetachLooperDeleter = void (*)(AInputQueue*);

public:
    AndroidLooper();

public:
    void prepare();
    bool pollEvent(AndroidEvent& event);
    void setInputQueue(AInputQueue* inputQueue);
    AInputQueue* inputQueue() const;

private:
    void pollFromInputQueue(AndroidEvent& event);
    void unexpectedIdentifier(int id);

private:
    int32_t dispatchEvent(AInputEvent* inputEvent, AndroidEvent& event);
    int32_t dispatchMotionEvent(AInputEvent* inputEvent, AndroidEvent& event);
    int32_t dispatchKeyEvent(AInputEvent* inputEvent, AndroidEvent& event);
    int32_t dispatchTouchEvent(AInputEvent* inputEvent, AndroidEvent& event);

private:
    ALooper* mLooper;
    std::unique_ptr<AInputQueue, DetachLooperDeleter> mInputQueue;
};

// enums

enum AndroidLooper::Id : int {
    ReservedId,
    InputQueueId,
};

enum AndroidLooper::Timeout : int {
    IndefinitelyUntilEventAppearsTimeout = -1,
    ImmediatelyWithoutBlockingTimeout = 0,
};
