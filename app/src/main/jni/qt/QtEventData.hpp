#pragma once

#include <cstdint>

struct QtTouchEvent {

    float x;
    float y;
};

struct QtResizeEvent {
    int32_t width;
    int32_t height;
};

union QtEventData {

    QtTouchEvent touchEvent;
    QtResizeEvent resizeEvent;
};
