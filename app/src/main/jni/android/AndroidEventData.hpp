#pragma once

// ndk
#include <android/native_activity.h>

struct AndroidTouchEvent {

    float x;
    float y;
};

struct AndroidResizeEvent {
    int32_t width;
    int32_t height;
};

struct AndroidNativeWindowEvent {
    ANativeWindow* pendingWindow;
};

struct AndroidInputQueueEvent {
    AInputQueue* pendingQueue;
};

struct AndroidEventLoopEvent {
    bool windowReady;
};

// main structure for all events
// it must contain all structures defined above

union AndroidEventData {

    AndroidTouchEvent touchEvent;
    AndroidResizeEvent resizeEvent;
    AndroidNativeWindowEvent nativeWindowEvent;
    AndroidInputQueueEvent inputQueueEvent;
    AndroidEventLoopEvent eventLoopEvent;
};
