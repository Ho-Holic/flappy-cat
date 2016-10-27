#ifndef FLAPPY_CAT_ANDROIDEVENTDATA_H
#define FLAPPY_CAT_ANDROIDEVENTDATA_H

struct AndroidMotionEvent {

  float x;
  float y;
};

struct AndroidResizeEvent {
  int32_t width;
  int32_t height;
};

union AndroidEventData {

  AndroidMotionEvent motionEvent;
  AndroidResizeEvent resizeEvent;
};

#endif //FLAPPY_CAT_ANDROIDEVENTDATA_H
