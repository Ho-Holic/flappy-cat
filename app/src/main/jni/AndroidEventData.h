#ifndef FLAPPY_CAT_ANDROIDEVENTDATA_H
#define FLAPPY_CAT_ANDROIDEVENTDATA_H

struct AndroidMotionEvent {

  float x;
  float y;
};

union AndroidEventData {

  AndroidMotionEvent motionEvent;
};

#endif //FLAPPY_CAT_ANDROIDEVENTDATA_H
