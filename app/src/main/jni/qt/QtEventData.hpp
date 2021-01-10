#pragma once

struct QtTouchEvent {

    float x;
    float y;
};

union QtEventData {

    QtTouchEvent  touchEvent;
};
